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
                <b-select v-model="$i18n.locale" :placeholder="$t('switch_lang')">
                    <option value="en">{{$t('ENGLISH')}}</option>
                    <option value="zh">{{$t('CHINESE')}}</option>
                    <option disabled="disabled">{{$t('JAPANESE')}}</option>
                </b-select>
                <div class="navbar-item" v-if="account === null && scatter">
                  <a class="button is-primary is-inverted is-rounded" @click="requestId">登录</a>
                </div>
                <div class="navbar-item" v-if="account === null && !scatter">
                  <a class="button is-primary is-inverted is-outlined is-rounded" href="https://get-scatter.com/" target="_blank">下载 Scatter 后登录</a>
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
    <footer class="footer">
      <div class="content has-text-centered">
        <p>
          <strong>EOS Celebrity</strong> Some Right Reserved.
        </p>
      </div>
    </footer>
  </div>
</template>

<script>
import { mapState, mapActions, mapGetters } from "vuex";
import { network } from "./config";
import InviteModal from "@/components/InviteModal";

const requiredFields = { accounts: [network] };

export default {
  name: "app",
  components: {
    InviteModal
  },
  data: () => ({
    isInviteDialogActive: false
  }),
  created() {
    // @TODO: replace with Scatter JS
    document.addEventListener("scatterLoaded", () => {
      console.log("Scatter Loaded");
      this.handleScatterLoaded();
    });

    if (Date.now() < 1539403200000) {
      this.$snackbar.open({
        message: "公告：北京时间 2018 年 10 月 13 日中午 12:00 正式开放购买",
        type: "is-warning",
        position: "is-top",
        actionText: "OK",
        indefinite: true
      });
    }
  },
  methods: {
    ...mapActions(["initScatter", "setIdentity"]),
    handleScatterLoaded() {
      const { scatter } = window;
      this.initScatter(scatter);
      // this.requestId();
    },
    async requestId() {
      await this.suggestNetworkSetting();
      const identity = await this.scatter.getIdentity(requiredFields);
      this.setIdentity(identity);
    },
    async forgetId() {
      await this.scatter.forgetIdentity();
      this.setIdentity(null);
    },
    async suggestNetworkSetting() {
      try {
        await this.scatter.suggestNetwork(network);
      } catch (error) {
        console.info("User canceled to suggestNetwork");
      }
    },
    invite() {
      this.isInviteDialogActive = true;
    },
    switchI18n(code) {
      console.info('Triggered Switch I18n to: ' + code)
      this.$i18n.locale = code
    }
  },
  computed: {
    ...mapState(["identity", "scatter", "eos"]),
    ...mapGetters(["account"])
  }
};
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
