export default {
  EOSCelebrity: 'EOS 加密名人',
  nav_switch_lang: '切换语言',
  nav_switch_lang_en: '英语',
  nav_switch_lang_zh: '中文',
  nav_switch_lang_jp: '日语',
  nav_celeb_list: '名人列表',
  nav_leaderboard: '排行榜',
  nav_about: '关于',
  nav_sign_in: '登录',
  nav_sign_in_scatter: '下载 Scatter 后登录',
  nav_invite: '邀请',
  nav_sign_out: '登出',
  info_pot: '奖池',
  info_count_down: '结束倒计时',
  info_count_down_end: '已结束',
  info_last_buyer: '最后买家',
  info_order_by: '排序',
  info_order_by_asc: '价格从低到高',
  info_order_by_desc: '价格从高到低',
  info_filter: '过滤',
  info_filter_none: '显示全部名人',
  info_filter_buy: '我的名人',
  info_filter_not_buy: '未拥有的名人',
  card_owner: '持有者',
  card_buy_after_login: '登录后购买',
  card_buy: '购买',
  card_edit_slogan: '修改标语',
  buy_modal_title: '购买',
  buy_modal_label: '购买价格',
  buy_modal_pay: '使用 Scatter 支付',
  buy_modal_cancel: '取消',
  buy_modal_msg_success: '您已成功以 {priceReadable} 购买 {buyTarget}。',
  buy_modal_msg_cancel: '您在 Scatter 中取消了 {buyTarget} 的购买。',
  buy_modal_msg_fail_title: '购买失败',
  buy_modal_msg_fail_body: '抱歉，以 {priceReadable} 购买 {buyTarget} 失败：<br>{content}',
  buy_modal_msg_fail_overdrawn: '您的账户余额不足',
  buy_modal_msg_fail_no_enough: '有人比您抢先一步买下了该名人',
  buy_modal_msg_fail_time: '还没有到开始时间，或已超过结束时间',
  invite_modal_title: '邀请好友获得奖励',
  invite_modal_label: '邀请链接',
  invite_modal_copy: '复制',
  invite_modal_close: '关闭',
  invite_modal_copy_success: '邀请链接已复制到剪贴板',
  invite_modal_copy_fail: '邀请链接复制失败，请手工复制',
  edit_slogan_modal_title: '修改标语',
  edit_slogan_modal_label: '标语内容 (最长 64 字符)',
  edit_slogan_modal_save: '保存标语',
  edit_slogan_modal_cancel: '取消',
  edit_slogan_modal_msg_success: '为 {sloganTarget} 设置标语成功！',
  edit_slogan_modal_msg_cancel: '您取消了对 {sloganTarget} 标语的设置。',
  edit_slogan_modal_msg_fail_title: '设置标语失败',
  edit_slogan_modal_msg_fail_body: '为 {sloganTarget} 设置标语失败：<br>未知错误：<br>{content}',
  leaderboard_label_rank: '排名',
  leaderboard_label_name: '用户',
  leaderboard_label_total_value: '总资产',
  leaderboard_label_celeb_count: '名人数',
  leaderboard_label_celeb_top: '拥有名人 (价值 TOP 5)',
  about_content: `
  <h2>定价说明</h2>
  <p>每个名人初始价格为 0.1 EOS</p>
  <p>下一次价格为：之前的价格*1.35.</p>
  <p>&nbsp;</p>
  <p>溢价的35% 按照以下比率分配</p>
  <ul>
    <li>前一个人拿 60%</li>
    <li>奖池 10%</li>
    <li>邀请者 10% 如无邀请者则 这笔钱会放到奖池</li>
    <li>团队 20% （ram费用及维护费用）</li>
  </ul>
  <h2>举个例子：</h2>
  <p>如特朗普当前价格为 10 EOS</p>
  <p>则我需要用 10*1.35=13.5 EOS 成交</p>
  <p>10 EOS 首先给前一个购买者</p>
  <p>剩下的 10*0.35=3.5 按照比率分配</p>
  <p>前一个人拿：3.5*60%=2.1 EOS</p>
  <p>奖池拿 3.5*10%=0.35</p>
  <p>邀请者拿 3.5 *10%=0.35</p>
  <p>团队拿 3.5*20%=0.7</p>
  `
}
