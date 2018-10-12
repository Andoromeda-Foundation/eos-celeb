<template>
  <div>
    <section class="hero is-primary is-bold">
      <div class="hero-head">
        <nav class="navbar is-spaced">
          <div class="container">
            <div class="navbar-brand">
              <div class="navbar-burger burger" data-target="navbarExampleTransparentExample">
                <span></span>
                <span></span>
                <span></span>
              </div>
            </div>
            <div class="navbar-menu">
              <div class="navbar-start">
                <a class="navbar-item" href="#">
                  首页
                </a>
                <a class="navbar-item" href="#">
                  名人列表
                </a>
                <a class="navbar-item" href="#">
                  关于
                </a>
              </div>
              <div class="navbar-end">
                <div class="navbar-item" v-if="account === null && scatter">
                  <a class="button is-primary is-inverted is-rounded" @click="requestId">&nbsp;&nbsp;登录&nbsp;&nbsp;</a>
                </div>
                <div class="navbar-item" v-if="account === null && !scatter">
                  <a class="button is-primary is-inverted is-outlined is-rounded" href="#">&nbsp;&nbsp;下载 Scatter 后登录&nbsp;&nbsp;</a>
                </div>
                <div class="navbar-item" v-if="account !== null">
                  {{account.name}} 已登录
                </div>
                <div class="navbar-item" v-if="account !== null">
                  <a class="button is-primary is-inverted is-outlined is-rounded" @click="forgetId">&nbsp;&nbsp;退出登录&nbsp;&nbsp;</a>
                </div>
              </div>
            </div>
          </div>
        </nav>
      </div>
      <div class="hero-body">
        <div class="container">
          <h1 class="title">
            加密名人
          </h1>
          <h2 class="subtitle">
            名人列表
          </h2>
        </div>
      </div>
    </section>
    <div class="body-container">
      <div class="container">
        <router-view />
      </div>
    </div>
  </div>
</template>

<script>
import { mapState, mapActions, mapGetters } from 'vuex'
import { network } from './config'

const requiredFields = { accounts: [network] }

export default {
  name: 'app',
  data: () => ({}),
  created () {
    // @TODO: replace with Scatter JS
    document.addEventListener('scatterLoaded', () => {
      console.log('Scatter Loaded')
      this.handleScatterLoaded()
    })
  },
  methods: {
    ...mapActions(['initScatter', 'setIdentity']),
    handleScatterLoaded () {
      const { scatter } = window
      this.initScatter(scatter)
      // this.requestId();
    },
    async requestId () {
      await this.suggestNetworkSetting()
      const identity = await this.scatter.getIdentity(requiredFields)
      this.setIdentity(identity)
    },
    async forgetId () {
      await this.scatter.forgetIdentity()
      this.setIdentity(null)
    },
    async suggestNetworkSetting () {
      try {
        await this.scatter.suggestNetwork(network)
      } catch (error) {
        console.info('User canceled to suggestNetwork')
      }
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos']),
    ...mapGetters(['account'])
  }
}
</script>

<style>
.body-container {
  padding: 3rem 0;
  background: #EEE;
}
</style>

<style lang="scss">
@import "~bulma/sass/utilities/_all";

// Set your colors
$primary: #51BCCF;
$primary-invert: findColorInvert($primary);

$colors: (
    "white": ($white, $black),
    "black": ($black, $white),
    "light": ($light, $light-invert),
    "dark": ($dark, $dark-invert),
    "primary": ($primary, $primary-invert),
    "info": ($info, $info-invert),
    "success": ($success, $success-invert),
    "warning": ($warning, $warning-invert),
    "danger": ($danger, $danger-invert),
);

$link: $primary;
$link-invert: $primary-invert;
$link-focus-border: $primary;

@import "~bulma";
@import "~buefy/src/scss/buefy";
</style>
