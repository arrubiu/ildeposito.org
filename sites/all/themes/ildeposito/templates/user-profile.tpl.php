<?php
/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>
<div class="profile"<?php print $attributes; ?>>

  <div class="profilo">
    <div class="grid-10 col-first">
      <?php if ($image_profile) {
        print $image_profile;
      } ?>
      <strong><?php print $nome_utente; ?></strong><br />
      Iscritto da <?php print $membro_dal; ?><br />
      <?php print $ruoli; ?><br />
      <?php
      if (isset($staff)) {
        print '<strong><em>' . $staff . '</em></strong><br />';
      }
      ?>

        <?php print render($user_profile['privatemsg_send_new_message']); ?><br />
        <?php        if ($GLOBALS['user']->uid == $elements['#account']->uid) {
          print 'Gestione ' . l('newsletter', 'user/' . $elements['#account']->uid . '/edit/simplenewsrender');
        } 
        ; ?>
    </div>
    <div class="grid-7 prefix-1col-second">
      <?php if (isset($field_messggio_personale)) : ?>
        <div id="messaggio-personale">
  <?php print render($user_profile['field_messggio_personale']); ?>
        </div>

<?php endif; ?>

    </div>

  </div>


  <div id="contents">
    <h2 class="block-title">Contenuti</h2>
<?php print views_embed_view('utente_contenuti', 'contenuti_blocco', $variables['elements']['#account']->name); ?>
    <h2 class="block-title">Commenti</h2>
<?php print views_embed_view('utente_commenti', 'commenti_block', $variables['elements']['#account']->name); ?>
  </div>

</div>
