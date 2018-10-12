import Vue from 'vue'
import Buefy from 'buefy'
import VueClipboard from 'vue-clipboard2'
import App from './App.vue'
import router from './router'
import store from './store'

Vue.use(Buefy)
Vue.use(VueClipboard)
Vue.config.productionTip = false

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
