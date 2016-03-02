#ifndef INFOSTRING_H
#define INFOSTRING_H

#include <QString>
#include <QTextCodec>

#define SUBJECT QTextCodec::codecForLocale()->toUnicode("商品备注")
#define DESCRIPTION QTextCodec::codecForLocale()->toUnicode("商品描述")
#define OPERATOR QTextCodec::codecForLocale()->toUnicode("操作员")
#define OWN_ORDER_ID QTextCodec::codecForLocale()->toUnicode("第三方应用订单号")
#define TOTAL_FEE QTextCodec::codecForLocale()->toUnicode("总金额，以分为单位的整数")
#define CARD_ID QTextCodec::codecForLocale()->toUnicode("客户付款码")
#define WOSAI_ORDER_ID QTextCodec::codecForLocale()->toUnicode("收款成功后自动填入")

#define SUBJECT_SAMPLE QTextCodec::codecForLocale()->toUnicode("饮料")
#define DESCRIPTION_SAMPLE QTextCodec::codecForLocale()->toUnicode("雪碧330ml")
#define OPERATOR_SAMPLE QTextCodec::codecForLocale()->toUnicode("张三")

#define LOAD_SDK_FAIL QTextCodec::codecForLocale()->toUnicode("加载SDK失败，请检查SDK路径是否正确！")

#define SUBJECT_EMPTY QTextCodec::codecForLocale()->toUnicode("商品备注不能为空")
#define STORE_ID_EMPTY QTextCodec::codecForLocale()->toUnicode("店铺ID不能为空")
#define OPERATOR_EMPTY QTextCodec::codecForLocale()->toUnicode("操作员不能为空")
#define OWN_ORDER_ID_EMPTY QTextCodec::codecForLocale()->toUnicode("第三方应用订单号不能为空")
#define TOTAL_FEE_EMPTY QTextCodec::codecForLocale()->toUnicode("总金额，以分为单位的整数不能为空")
#define WOSAI_ORDER_ID_EMPTY QTextCodec::codecForLocale()->toUnicode("Wosai生成的订单号不能为空")
#define PAY_METHOD_EMPTY QTextCodec::codecForLocale()->toUnicode("当前模式下必须选择支付方法")
#define CARD_ID_EMPTY QTextCodec::codecForLocale()->toUnicode("当前模式下必须填写付款码")
#define ORDER_ID_AND_TOTAL_FEE_EMPTY QTextCodec::codecForLocale()->toUnicode("当前模式下必须填写Wosai订单号及退款金额")
#define OWN_AND_WOSAI_ORDER_ID_EMPTY QTextCodec::codecForLocale()->toUnicode("第三方应用订单号和Wosai生成的订单号不能同时为空")

#define SELECT_QRCODE_PATH QTextCodec::codecForLocale()->toUnicode("请选择二维码保存路径")

#define REQUEST_CALL QTextCodec::codecForLocale()->toUnicode(">:")
#define REQUEST_RESULT QTextCodec::codecForLocale()->toUnicode("<:")

#define ALIPAY_STR QTextCodec::codecForLocale()->toUnicode("支付宝")
#define WECHAT_STR QTextCodec::codecForLocale()->toUnicode("微信")
#define UNIONPAY_STR QTextCodec::codecForLocale()->toUnicode("银联")
#define BAIDU_STR QTextCodec::codecForLocale()->toUnicode("百度")
#define JDPAY_STR QTextCodec::codecForLocale()->toUnicode("京东")
#define UNDEFINE_STR QTextCodec::codecForLocale()->toUnicode("未指定")

#define LOAD_SDK_STR QTextCodec::codecForLocale()->toUnicode("加载SDK")
#define UNLOAD_SDK_STR QTextCodec::codecForLocale()->toUnicode("卸载SDK")

#define AUTH_VENDOR_INPUT QTextCodec::codecForLocale()->toUnicode("请输入供应商信息")
#define AUTH_KEY_INPUT QTextCodec::codecForLocale()->toUnicode("请输入供应商授权")
#define AUTH_CODE_INPUT QTextCodec::codecForLocale()->toUnicode("请输入激活码")
#define SELECT_SDK_PATH QTextCodec::codecForLocale()->toUnicode("请选择SDK路径")

#endif // INFOSTRING_H
