<template>
  <div id="app" class="container">
    <nav class="level" style="height: 4rem">
      <div class="level-left">
        <router-link to="/" class="level-item has-text-centered">Home</router-link>
        <router-link to="/about" class="level-item has-text-centered">About</router-link>
      </div>
      <div class="level-right" v-if="account !== null">
            <p class="level-item has-text-centered">
              {{account.name}} 已登录
            </p>
            <button class="button" @click="forgetId">退出登录</button>
      </div>
    </nav>
    <div class="please-login" v-if="account === null">
      <section class="hero is-primary">
        <div class="hero-body">
          <div class="container">
            <h1 class="title">
              欢迎来到加密名人
            </h1>
            <h2 class="subtitle">
              请使用钱包进行登录以继续
            </h2>
            <button class="button" @click="requestId" :disabled="!scatter"> 登录 </button>
          </div>
        </div>
      </section>
    </div>
    <router-view v-else/>
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
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  /* text-align: center; */
  color: #2c3e50;
}
#nav {
  padding: 30px;
}

#nav a {
  font-weight: bold;
  color: #2c3e50;
}

#nav a.router-link-exact-active {
  color: #42b983;
}
</style>
