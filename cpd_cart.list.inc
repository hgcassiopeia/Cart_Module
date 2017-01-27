<?php

function cpd_cart_list($form,&$form_state){
    $form = array();

    $query = db_select('ck_product','ck')->extend('PagerDefault');
    $query->join('ck_types','t','t.ck_tid = ck.ck_type');
    $query
        ->fields('ck',array('ck_id','ck_name','ck_price'))
        ->fields('t',array('ck_tname'))
        ->orderBy('ck_tname','DESC');
    $results = $query->execute();

    $header = array(
        t('Product'),
        t('Type'),
        t('Price (฿)'),
    );

    $options = array();
    foreach ($results as $result){
        $options[$result->ck_id] = array(
            $result->ck_name,
            $result->ck_tname,
            $result->ck_price,
        );
    }

    $form['table'] = array(
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $options,
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Remove'),
        '#submit' => array('cpd_cart_list_form_submit' ),
    );

    return $form;
}

function cpd_cart_list_form_submit($form,&$form_state){
    foreach (($form_state['values']['table']) as $results => $result) {
        if($result) {
            $ck_id = $results;
            $delete = db_delete('ck_product')
                -> condition('ck_id',$ck_id)
                -> execute();
        }
    }
}