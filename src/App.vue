<template>
  <div>
    <section class="hero is-primary is-bold">
      <div class="hero-head">
        <nav class="navbar is-spaced">
          <div class="container">
            <div class="navbar-brand">
              <div class="navbar-burger burger" @click="switchNav()">
                <span></span>
                <span></span>
                <span></span>
              </div>
            </div>
            <div :class="['navbar-menu', { 'is-active': isNavActive }]">
              <div class="navbar-start">
                <router-link to="/leaderboard" class="navbar-item">
                  {{$t('nav_leaderboard')}}
                </router-link>
                <router-link to="/" class="navbar-item">
                  {{$t('nav_celeb_list')}}
                </router-link>
                <router-link to="/about" class="navbar-item">
                  {{$t('nav_about')}}
                </router-link>
              </div>
              <div class="navbar-end">
                <div class="navbar-item">
                  <b-select rounded v-model="$i18n.locale" :placeholder="$t('nav_switch_lang')">
                    <option value="en">{{$t('nav_switch_lang_en')}}</option>
                    <option value="zh">{{$t('nav_switch_lang_zh')}}</option>
                    <option disabled="disabled">{{$t('nav_switch_lang_jp')}}</option>
                  </b-select>
                </div>
                <div class="navbar-item" v-if="account === null && scatter">
                  <a class="button is-primary is-inverted is-rounded" @click="requestId">{{$t('nav_sign_in')}}</a>
                </div>
                <div class="navbar-item" v-if="account === null && !scatter">
                  <a class="button is-primary is-inverted is-outlined is-rounded" href="https://get-scatter.com/" target="_blank">{{$t('nav_sign_in_scatter')}}</a>
                </div>
                <div class="navbar-item" v-if="account !== null">
                  Welcome {{account.name}}
                </div>
                <div class="navbar-item" v-if="account !== null">
                  <a class="button is-primary is-inverted is-outlined is-rounded" @click="invite">{{$t('nav_invite')}}</a>
                </div>
                <a class="navbar-item" v-if="account !== null" @click="forgetId">
                  {{$t('nav_sign_out')}}
                </a>
              </div>
            </div>
          </div>
        </nav>
      </div>
      <div class="hero-body">
        <div class="container">
          <h1 class="title">
            {{ $t('EOSCelebrity') }}
          </h1>
        </div>
      </div>
    </section>
    <div class="body-container">
      <div class="container">
        <router-view />
      </div>
    </div>
    <b-modal :active.sync="isInviteDialogActive" has-modal-card>
      <invite-modal></invite-modal>
    </b-modal>
    <footer class="footer has-background-grey-dark has-text-light">
      <div class="content has-text-centered">
        <p>
          <strong class="has-text-white">EOS Celebrity</strong> Some Right Reserved.
        </p>
      </div>
    </footer>
  </div>
</template>

<script>
import { mapState, mapActions, mapGetters } from 'vuex'
import { network } from './config'
import InviteModal from '@/components/InviteModal'

const requiredFields = { accounts: [network] }

export default {
  name: 'app',
  components: {
    InviteModal
  },
  data: () => ({
    isInviteDialogActive: false,
    isNavActive: false
  }),
  created () {
    // @TODO: replace with Scatter JS
    document.addEventListener('scatterLoaded', () => {
      console.log('Scatter Loaded')
      this.handleScatterLoaded()
    })

    if (Date.now() < 1539432000000) {
      this.$snackbar.open({
        message: this.$t('announcement'),
        type: 'is-warning',
        position: 'is-top',
        actionText: 'OK',
        indefinite: true
      })
    }
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
    switchNav () {
      this.isNavActive = !this.isNavActive
    },
    invite () {
      this.isInviteDialogActive = true
    },
    switchI18n (code) {
      console.info('Triggered Switch I18n to: ' + code)
      this.$i18n.locale = code
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos']),
    ...mapGetters(['account'])
  }
}
</script>

<style>
html {
  height: 100%;
}

body {
  min-height: 100%;
}

body,
html {
  background: #f0f0f0;
}

.navbar .button {
  padding-left: 1.5rem !important;
  padding-right: 1.5rem !important;
}

.global-info {
  padding-bottom: 3rem;
}

.body-container {
  margin: 3rem 0;
}
</style>

<style lang="scss">
@import "~bulma/sass/utilities/_all";

// Set your colors
$primary: #51bccf;
$primary-invert: findColorInvert($primary);

$colors: (
  "white": (
    $white,
    $black
  ),
  "black": (
    $black,
    $white
  ),
  "light": (
    $light,
    $light-invert
  ),
  "dark": (
    $dark,
    $dark-invert
  ),
  "primary": (
    $primary,
    $primary-invert
  ),
  "info": (
    $info,
    $info-invert
  ),
  "success": (
    $success,
    $success-invert
  ),
  "warning": (
    $warning,
    $warning-invert
  ),
  "danger": (
    $danger,
    $danger-invert
  )
);

$link: $primary;
$link-invert: $primary-invert;
$link-focus-border: $primary;

@import "~bulma";
@import "~buefy/src/scss/buefy";
</style>
