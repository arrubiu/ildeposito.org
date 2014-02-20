/**
 * @file
 * Varnish Agent dashboard tool.
 *
 * Fetches stats and data from the Varnish Agent, aggregates it, and presents it.
 */

(function ($) {

  Drupal.behaviors.varnishDashboard = {
    attach: function (context, settings) {
      VarnishAgentDashboard.init();
    }
  };

})(jQuery);




VarnishAgentDashboard = {

  // Data-points used by the application.
  data: {
    stats: [],
  },

  // Application config.
  config: {},

  // Default config.
  default_config: {
    // Default config of the application aspects.
    app: {
      // URL of the Varnish Agent (or proxy).
      agent_base_url: 'http://vm-vdashbrd.local/proxy_varnish_dashboard',
      // Average out stats over the last 10 data-points.
      smoothness: 10,
      // Time (in milliseconds) between each request to the Agent service.
      refresh_time: 1000,
    },

    // Default config of the presentation aspects.
    presentation: {
      // Peak value for the requests throughput widget (in requests-per-second).
      scale_requests_per_second: 3000,
      // Peak value for the bandwidth widget (in Mbps).
      scale_bandwidth: 50,
      // Time (in milliseconds) between each refresh of the display.
      refresh_time: 1000,
    },
  },


  /**
   * Add a single stats data-point to the data-set.
   */
  addStats: function(stats) {
    // Remove the oldest stats entry, if the limit of smoothness is reached.
    if (this.data.stats.length >= this.config.app.smoothness) {
      this.data.stats.shift();
    }
    // Attach timestamp (milliseconds since Unix epoch).
    stats.timestamp = new Date().getTime();

    this.data.stats.push(stats);

    // Infer stats (Using the full data-set).
    this.calculateInferredStats();
  },


  // Get the data-point for a single data-item.
  get: {
    
    cacheHitRatio: function() {
      // The metric 'cache_hit' gives a count of cache hits, not a ratio.
      // Calculate the *delta* of new hits since the last lookup, divide
      // against the *delta* of new requests since the last lookup.
      var dataset = [];
      for (var i=0; i<this.data.stats.length; ++i) {
        dataset.push(this.data.stats[i].inferred.cache_hit_ratio);
      }
      return dataset.length == 0 ? 0 : Math.round(100 * this.smooth(dataset));
    },

    requestsPerSecond: function() {
      // Use the 'client_req' metric to calculate requests-per-second.
      var dataset = [];
      for (var i=0; i<this.data.stats.length; ++i) {
        dataset.push(this.data.stats[i].inferred.requests_per_second);
      }
      return dataset.length == 0 ? 0 : this.smooth(dataset);
    },

    bandwidth: function() {
      // Use the metrics 's_hdrbytes' and 's_bodybytes' to calculate data-transfer total.
      var dataset = [];
      for (var i=0; i<this.data.stats.length; ++i) {
        dataset.push(this.data.stats[i].inferred.bandwidth);
      }
      // Adjust bandwidth to return in Megabits/second.
      return dataset.length == 0 ? 0 : (this.smooth(dataset) / 1024 / 1024);
    },



    cacheMetrics: function() {
      // The latest data-set.
      var stat = this.data.stats[this.data.stats.length - 1];

      // Base all 'current' values on a nominal period of 1 second.
      multiplier = (1000 / stat.inferred.interval);

      var hits_ratio = {
        label: "Hits Ratio",
        // Hit ratio in last request.
        new_value: this.get.cacheHitRatio.call(this) ? this.get.cacheHitRatio.call(this) : "N/A",
        // Use total of all metric to-date, not just last second.
        average_value: (stat.client_req.value == 0)
          ? "N/A"
          // Multiply by 100, to provide a percentage. Round to nearest int.
          : Math.round(100 * (stat.cache_hit.value / stat.client_req.value))
      }
      var hits_qty = {
        label: "Hits Qty.",
        new_value: this.nFormatter(multiplier * this.getDelta('cache_hit')),
        average_value: this.nFormatter(stat.cache_hit.value)
      }
      var miss_qty = {
        label: "Miss Qty.",
        new_value: this.nFormatter(multiplier * this.getDelta('cache_miss')),
        average_value: this.nFormatter(stat.cache_miss.value)
      }
      var obj_cache = {
        label: "Objs. in Cache",
        new_value: this.nFormatter(multiplier * this.getDelta('n_object')),
        average_value: this.nFormatter(stat.n_object.value)
      }
      return [hits_ratio, hits_qty, miss_qty, obj_cache]
    },



    trafficMetrics: function() {
      // The latest data-set.
      var stat = this.data.stats[this.data.stats.length - 1];

      // Base all 'current' values on a nominal period of 1 second.
      multiplier = (1000 / stat.inferred.interval);

      var client_conn = {
        label: "Connections",
        new_value: this.nFormatter(multiplier * this.getDelta('client_conn')),
        average_value: this.nFormatter(stat.client_conn.value)
      }
      var client_req = {
        label: "Requests",
        new_value: this.nFormatter(multiplier * this.getDelta('client_req')),
        average_value: this.nFormatter(stat.client_req.value)
      }
      var req_per_conn = {
        label: "Req / Conn",
        new_value: (this.getDelta('client_conn') == 0)
          ? 0
          : this.nFormatter(this.getDelta('client_req') / this.getDelta('client_conn')),
        average_value: (stat.client_conn.value == 0)
          ? 0
          : this.nFormatter(stat.client_req.value / stat.client_conn.value)
      }
      var bandwith = {
        label: "Bandwidth",
        new_value: this.nFormatter(multiplier * stat.inferred.traffic_new),
        // Divide by uptime, to provide aggregate bandwidth usage.
        average_value: this.nFormatter((stat.s_hdrbytes.value + stat.s_bodybytes.value) / stat.uptime.value)
      }

      return [client_conn, client_req, req_per_conn, bandwith]
    },

    backendMetrics: function() {
       // The latest data-set.
       var stat = this.data.stats[this.data.stats.length - 1];

       // Base all 'current' values on a nominal period of 1 second.
       multiplier = (1000 / stat.inferred.interval);

       var backend_conn = {
         label: "Connections",
         new_value: this.nFormatter(this.getDelta('backend_conn')),
         average_value: this.nFormatter(this.getValue('backend_conn'))
       }
       var backend_fail = {
         label: "Fails",
         new_value: this.nFormatter(this.getDelta('backend_fail')),
         average_value: this.nFormatter(this.getValue('backend_fail'))
       }
       var backend_reuse = {
         label: "Reuse",
         new_value: this.nFormatter(this.getDelta('backend_reuse')),
         average_value: this.nFormatter(this.getValue('backend_reuse'))
       }
       var backend_fetch = {
         label: "Fetch & Pass",
         new_value: this.nFormatter(this.getDelta('s_pass') + this.getDelta('s_fetch')),
         average_value: this.nFormatter(this.getValue('s_pass') + this.getValue('s_fetch') / this.getValue('uptime'))
       }

       return [backend_conn, backend_fetch, backend_fail, backend_reuse]
     }
  },

  /**
   * Smooth a set of n data-points to a single (mean) value.
   */
  smooth: function(dataset) {
    // Initial version: mean.
    var sum = 0;
    for (var i=0; i<dataset.length; ++i) {
      sum += dataset[i];
    }
    return sum / dataset.length;
  },

  /**
   * Attach inferred metrics to the latest stats.
   * Infer:
   * - Requests per second (using 'client_req' as the data-source).
   * - Bandwidth (using 's_hdrbytes' and 's_bodybytes' as the data-source).
   */
  calculateInferredStats: function() {
    var i = this.data.stats.length - 1;

    // If there's only a second metric, the stats can't be inferred.
    if (i < 1) {
      this.data.stats[i].inferred = {
        ínterval: 0,
        requests_per_second: 0,
        bandwidth: 0,
        bandwidthNew: 0,
        cache_hit_ratio: 0,
        cache_hit_new: 0,
        cache_miss_new: 0,
        n_object_new: 0,
        client_conn_new: 0
      };
      return;
    }


    // Interval between the 2 stats-points (in milliseconds).
    var interval = this.data.stats[i].timestamp - this.data.stats[i-1].timestamp;

    // Calculate the difference between this request and the last.
    var newCacheHits = this.getDelta('cache_hit');
    var newRequests = this.getDelta('client_req');

    // New bandwidth handled (in bytes) since last request.
    var newBandwidth = this.getDelta('s_hdrbytes') + this.getDelta('s_bodybytes');


    // Infer the datapoints and attach to the data object.
    this.data.stats[i].inferred = {
      interval: interval,
      cache_hit_ratio: (newRequests === 0) ? 0 : (newCacheHits / newRequests),
      requests_per_second: (newRequests / interval) * 1000,
      bandwidth: (newBandwidth / interval) * 1000,
      traffic_new: newBandwidth
    };
  },


  // Fetch the stats from the backend.
  fetchStats: function() {
    var url = this.config.app.agent_base_url + '/stats';

    // Use jQuery to fetch the data, and call App.addStats.
    jQuery.getJSON(url, function(data){
      VarnishAgentDashboard.addStats(data);
    });
  },

  // Initialise the application.
  init: function() {
    this.config = this.default_config;

    // Make 2 requests, and dispose of the first, to initialise the stats.
    this.fetchStats.call(this);
    this.fetchStats.call(this);
    this.data.stats.shift();

    this.presentation.init.call(this);

    setInterval(function() {VarnishAgentDashboard.fetchStats();}, this.config.app.refresh_time);
    setInterval(function() {VarnishAgentDashboard.presentation.refreshDisplay.call(VarnishAgentDashboard);}, this.config.presentation.refresh_time);
  },



  /**
   * Presentation framework.
   */
  presentation: {

    hitRatioGauge: {},
    requestGauge: {},
    bandwidthGauge: {},

    init: function() {
      // Initialise the gauges using JustGage objects.
      this.presentation.hitRatioGauge = new JustGage({
        id: "hit-ratio", 
        value: 0,
        levelColors: ["#f70000","#f9c800","#a8d600"],
        min: 0,
        max: 100,
        title: " ",
        label: "%"
      });

      this.presentation.requestGauge = new JustGage({
        id: "request-gauge", 
        value: 0, 
        min: 0,
        max: this.config.presentation.scale_requests_per_second,
        title: " ",
        label: "per second"
      });

      this.presentation.bandwidthGauge = new JustGage({
        id: "bandwidth-gauge", 
        value: 0, 
        min: 0,
        max: this.config.presentation.scale_bandwidth,
        title: " ",
        levelColors: ["#40b7f1","#40b7f1","#40b7f1"],
        label: "Mbps"
      });

      if (this.data.stats.length) {
        this.presentation.refreshDisplay.call(this);
      }
    },

    // Refresh the display to show the latest metrics.
    refreshDisplay: function() {
      // Refresh the gauges.
      this.presentation.hitRatioGauge.refresh(this.get.cacheHitRatio.call(this));
      this.presentation.requestGauge.refresh(this.get.requestsPerSecond.call(this));
      this.presentation.bandwidthGauge.refresh(this.get.bandwidth.call(this));

      // Build the metric tables.
      this.presentation.buildMetricsTable("cache",   this.get.cacheMetrics.call(this));
      this.presentation.buildMetricsTable("traffic", this.get.trafficMetrics.call(this));
      this.presentation.buildMetricsTable("backend", this.get.backendMetrics.call(this));
    },

    buildMetricsTable: function(table_id, data_values) {
      // The handlebar template should be in the main dashboard tpl.
      var source   = jQuery("#metrics-table-template").html();
      var context = { metric: data_values};
      var template = Handlebars.compile(source);
      var html = template(context);
      jQuery("#"+table_id+"-metrics-table").html(html);
    }
  },

  // Format a number to a human-readable string.
  nFormatter: function(num) {
    if (num >= 1000000000) {
      return (num / 1000000000).toFixed(1).replace(/\.0$/, '') + 'G';
    }
    if (num >= 1000000) {
      return (num / 1000000).toFixed(1).replace(/\.0$/, '') + 'M';
    }
    if (num >= 1000) {
      return (num / 1000).toFixed(1).replace(/\.0$/, '') + 'K';
    }
    // Default: just round to an integer.
    return Math.round(num);
  },


  // Get the value of a field in the latest dataset.
  getValue: function (field) {
    latest = this.data.stats.length - 1;
    if (latest <= 0) {
      return 0;
    }
    return this.data.stats[latest][field].value;
  },

  // Get the difference between this stat and the last.
  getDelta: function (field) {
    latest = this.data.stats.length - 1;
    if (latest <= 1) {
      return 0;
    }
    metric_new = this.data.stats[latest][field];
    metric_old = this.data.stats[latest-1][field];
    return (metric_new.value - metric_old.value);
  }

};
