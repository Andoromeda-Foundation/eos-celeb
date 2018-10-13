import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/CelebertiesList.vue'
import Owner from './views/OwnerList.vue'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/owners',
      name: 'Owners',
      component: Owner
    },
    {
      path: '/invite/:account',
      name: 'Invite',
      component: Home
    },
    {
      path: '/about',
      name: 'about',
      // route level code-splitting
      // this generates a separate chunk (about.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import(/* webpackChunkName: "about" */ './views/About.vue')
    }
  ]
})
