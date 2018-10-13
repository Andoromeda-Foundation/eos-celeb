import Vue from 'vue'
import VueI18n from 'vue-i18n'
import { messages } from './locales'
// import en from "./locales/en";
// import { i18n } from '@/config'

Vue.use(VueI18n)

// const messages = {
//   'zh': zh_CN,
//   'en': en
// }

// i18n.forEach((item) => {
//   // eslint-disable-next-line
//   const locale = require(`./locales/${item.locale}`);
//   item.aliases.forEach((alias) => {
//     messages[alias] = locale
//   })
// })

export default new VueI18n({
  locale: 'zh',
  fallbackLocale: 'en',
  messages
})
