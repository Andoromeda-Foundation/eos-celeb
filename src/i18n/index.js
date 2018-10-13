import Vue from 'vue'
import VueI18n from 'vue-i18n'
import { messages } from './locales'

Vue.use(VueI18n)

const savedLocale = localStorage.getItem('eos_celeb_locale')
let locale = 'zh'
if (['zh', 'en'].indexOf(savedLocale) > -1) {
  locale = savedLocale
}

export default new VueI18n({
  locale,
  fallbackLocale: 'en',
  messages
})
