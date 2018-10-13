<template>
  <form action="">
    <div class="modal-card" style="min-width: 500px; width: auto">
      <header class="modal-card-head">
        <p class="modal-card-title">邀请好友获得奖励</p>
      </header>
      <section class="modal-card-body">
        <b-field label="邀请连接">
          <b-field>
            <b-input
              id="refLink"
              v-bind:value="getRefer()"
              readonly
              expanded>
            </b-input>
            <p class="control">
              <a class="button is-primary" @click="copy">
                复制
              </a>
            </p>
          </b-field>
        </b-field>
      </section>
      <footer class="modal-card-foot">
        <button class="button is-rounded" @click="$parent.close()">关闭</button>
      </footer>
    </div>
  </form>
</template>

<script>
import { mapState, mapGetters } from 'vuex'

export default {
  name: 'InviteModal',
  methods: {
    getRefer () {
      const loc = window.location
      return `${loc.protocol}//${loc.host}/?#/invite/${this.account.name}`
    },
    copy () {
      this.$copyText(this.getRefer()).then(() => {
        this.$toast.open({
          message: '邀请链接已复制到剪贴板',
          type: 'is-success',
          duration: 3000,
          position: 'is-bottom',
          queue: false
        })
        this.$parent.close()
      }, () => {
        this.$toast.open({
          message: '邀请链接复制失败，请手工复制',
          type: 'is-danger',
          duration: 5000,
          position: 'is-bottom',
          queue: false
        })
      })
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos', 'account']),
    ...mapGetters(['account'])
  }
}
</script>
