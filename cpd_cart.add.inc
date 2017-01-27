<?php

function cpd_cart_AddForm(){
    $form = array();
    $form['product'] = array(
        '#type' => 'fieldset',
        '#title' => 'Add Product'
    );

    $form['product']['ck_type']=array(
        '#type'=>'select',
        '#title'=> t('Product Type'),
        '#options' => array(
            1 => t('Manga'),
            2 => t('Novel'),
            3 => t('Merchandise'),
        ),
    );

    $form['product']['ck_name']=array(
        '#type'=>'textfield',
        '#title'=> t('Product Name'),
    );

    $form['product']['ck_no']=array(
        '#type'=>'textfield',
        '#title'=> t('No.'),
    );

    $form['product']['ck_price']=array(
        '#type'=>'textfield',
        '#title'=> t('Price'),
    );

    $form['product']['ck_date'] = array(
        '#type' => 'date_popup',
        '#date_format' => 'd-m-Y',
    );

    $form['submit']=array(
        '#type'=>'submit',
        '#value'=>'Add Product'
    );

    $form['#submit'][]='cpd_cart_AddForm_submit';

    return $form;
}

function cpd_cart_AddForm_submit($form,&$form_state){
    $ck_id = db_insert('ck_product')
        ->fields(array(
            'ck_type' => $form_state['values']['ck_type'],
            'ck_name'=> $form_state['values']['ck_name'],
            'ck_no'=> $form_state['values']['ck_no'],
            'ck_price'=> $form_state['values']['ck_price'],
            'ck_date' => $form_state['values']['ck_date'],
        ))->execute();
    drupal_set_message("Successfully ".$form_state['values']['ck_name']." Added");
}