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
                <router-link to="/" class="navbar-item">
                  名人列表
                </router-link>
                <router-link to="/about" class="navbar-item">
                  关于
                </router-link>
              </div>
              <div class="navbar-end">
                <div class="navbar-item" v-if="account === null && scatter">
                  <a class="button is-primary is-inverted is-rounded" @click="requestId">登录</a>
                </div>
                <div class="navbar-item" v-if="account === null && !scatter">
                  <a class="button is-primary is-inverted is-outlined is-rounded" href="#">下载 Scatter 后登录</a>
                </div>
                <div class="navbar-item" v-if="account !== null">
                  {{account.name}} 已登录
                </div>
                <div class="navbar-item" v-if="account !== null">
                  <a class="button is-primary is-inverted is-outlined is-rounded" @click="invite">邀请</a>
                </div>
                <a class="navbar-item" v-if="account !== null" @click="forgetId">
                  退出登录
                </a>
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
        </div>
      </div>
    </section>
    <div class="container global-info">
      <nav class="level" v-if="globalInfo">
        <div class="level-item has-text-centered">
          <div>
            <p class="heading">奖池大小</p>
            <p class="title">{{ (globalInfo.pool / 10000).toFixed(4) }} EOS</p>
          </div>
        </div>
        <div class="level-item has-text-centered">
          <div>
            <p class="heading">结束倒计时</p>
            <p class="title">{{ globalCountdown }}</p>
          </div>
        </div>
      </nav>
    </div>
    <div class="body-container">
      <div class="container">
        <router-view />
      </div>
    </div>
    <b-modal :active.sync="isInviteDialogActive" has-modal-card>
      <invite-modal></invite-modal>
    </b-modal>
  </div>
</template>

<script>
import { mapState, mapActions, mapGetters } from 'vuex'
import { network } from './config'
import InviteModal from '@/components/InviteModal'

const requiredFields = { accounts: [network] }

function padTimeZero(str) {
  let t = '00' + str;
  return t.slice(t.length - 2, t.length);
}

export default {
  name: 'app',
  components: {
    InviteModal
  },
  data: () => ({
    globalCountdown: '00:00:00',
    isInviteDialogActive: false,
  }),
  created () {
    // @TODO: replace with Scatter JS
    document.addEventListener('scatterLoaded', () => {
      console.log('Scatter Loaded')
      this.handleScatterLoaded()
    })
    setInterval(() => {
      if (this.globalInfo != null) {
        const currentTimestamp = ~~(Date.now() / 1000);
        if (currentTimestamp >= this.globalInfo.ed) {
          this.globalCountdown = '已结束'
        } else {
          let remaining = this.globalInfo.ed - currentTimestamp;
          const seconds = remaining % 60
          remaining = ~~(remaining / 60)
          const minutes = remaining % 60
          remaining = ~~(remaining / 60)
          const hours = remaining
          this.globalCountdown = `${padTimeZero(hours)}:${padTimeZero(minutes)}:${padTimeZero(seconds)}`
        }
      }
    }, 1000)
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
    },
    invite () {
      this.isInviteDialogActive = true;
    },
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos', 'globalInfo']),
    ...mapGetters(['account'])
  },
}
</script>

<style>
html {
  height: 100%;
}

body {
  min-height: 100%;
}

body, html {
  background: #F0F0F0;
}

.navbar .button {
  padding-left: 1.5rem !important;
  padding-right: 1.5rem !important;
}

.global-info {
  padding: 3rem 0;
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
