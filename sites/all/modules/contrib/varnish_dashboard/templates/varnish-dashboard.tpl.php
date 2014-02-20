<div class="varnish-dashboard container">

  <div class="row-fluid">
    <div class="span4">
      <div class="content-box">
        <div class="content-box-header">
          <i class="icon-fire"></i>
          Cache Hit Ratio
        </div>
        <div id="hit-ratio" class="text-center gauge" style="width:250px; height:200px"></div>
      </div>
    </div>

    <div class="span4">
      <div class="content-box">
        <div class="content-box-header">
          <i class="icon-globe"></i>
          Requests
        </div>
        <div id="request-gauge" class="text-center gauge" style="width:250px; height:200px"></div>
      </div>
    </div>

    <div class="span4">
      <div class="content-box">
        <div class="content-box-header">
          <i class="icon-globe"></i>
          Bandwidth
        </div>
        <div id="bandwidth-gauge" class="text-center gauge" style="width:250px; height:200px"></div>
      </div>
    </div>
  </div> <!-- /row -->


  <div class="row-fluid">
    <div class="span4">
      <div class="content-box">
        <div class="content-box-header">
          <span class="icon-signal"></span>
          Cache Metrics
        </div>
        <div id="cache-metrics-table"></div>
      </div>
    </div>

    <div class="span4">
      <div class="content-box">
        <div class="content-box-header">
          <span class="icon-signal"></span>
          Traffic Metrics
        </div>
        <div id="traffic-metrics-table"></div>
      </div>
    </div>

    <div class="span4">
      <div class="content-box">
        <div class="content-box-header">
          <span class="icon-signal"></span>
          Backend Metrics
        </div>
        <div id="backend-metrics-table"></div>
      </div>
    </div>
  </div> <!-- /row -->
  
</div>

<?php // Handlebars templates, for generating the metric-tables. ?>
<script id="metrics-table-template" type="text/x-handlebars-template">
  <table class="table table-striped">
    <thead>
      <tr>
        <th></th>
        <th style="text-align:center;"><?php echo t('Current'); ?></th>
        <th style="text-align:center;"><?php echo t('Average'); ?></th>
      </tr>
    </thead>
    <tbody>
      {{#each metric}}
        <tr>
          <td>{{this.label}}</td>
          <td class="metric-value" style="text-align:right;">{{this.new_value}}</td>
          <td class="metric-value" style="text-align:right;">{{this.average_value}}</td>
        </tr>
      {{/each}}
    </tbody>
  </table>
</script>
