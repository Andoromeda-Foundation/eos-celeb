// import queryString from 'query-string'
import Vue from 'vue'
import Buefy from 'buefy'
import VueClipboard from 'vue-clipboard2'
import App from './App.vue'
import router from './router'
import i18n from './i18n'
import store from './store'

Vue.use(Buefy)
Vue.use(VueClipboard)
Vue.config.productionTip = false

new Vue({
  router,
  store,
  i18n,
  render: h => h(App)
}).$mount('#app')

// // Store referrer
// Use Router's params instead of this
// const qs = queryString.parse(location.search)
// if (qs.ref) {
//   console.log('Referrer: %s', qs.ref)
//   localStorage.setItem('eos_celeb_referrer', qs.ref)
// }
