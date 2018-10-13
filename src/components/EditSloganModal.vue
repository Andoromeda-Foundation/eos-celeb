<template>
  <form action="">
    <div class="modal-card" style="min-width: 500px; width: auto">
      <header class="modal-card-head">
        <p class="modal-card-title">修改标语</p>
      </header>
      <section class="modal-card-body">
        <b-field label="标语内容 (最长 64 字符)">
          <b-input maxlength="64" type="textarea" v-model="slogan"></b-input>
        </b-field>
      </section>
      <footer class="modal-card-foot">
        <button class="button is-rounded is-primary" @click="edit()">保存修改</button>
        <button class="button is-rounded" @click="$parent.close()">取消</button>
      </footer>
    </div>
  </form>
</template>

<script>
import { mapState, mapGetters } from 'vuex'
import * as API from '../blockchain/celeb'
import * as util from '../blockchain/util'

export default {
  name: 'EditSloganModal',
  props: ['priceInfo'],
  data: () => ({
    slogan: '',
  }),
  mounted: function () {
    // Initialize default value
    this.slogan = this.priceInfo.slogan
  },
  methods: {
    async edit() {
      const sloganTarget = this.celebBaseList[this.priceInfo.id].name
      try {
        await API.changeMySlogan({
          from: this.account.name,
          id: this.priceInfo.id,
          memo: this.slogan,
        })
        this.$toast.open({
          type: 'is-success',
          duration: 5000,
          message: `为 ${sloganTarget} 设置标语成功！`,
          position: 'is-bottom',
          queue: false
        })
        this.$parent.close()
        this.$store.dispatch('updateCeleb')
      } catch (error) {
        if (typeof error === 'object') {
          if (error.message.indexOf('User rejected the signature request') > -1) {
            this.$parent.close()
            this.$toast.open({
              type: 'is-danger',
              duration: 5000,
              message: `您取消了对 ${sloganTarget} 标语的设置。`,
              position: 'is-bottom',
              queue: false
            })
          } else {
            this.$dialog.alert({
              title: '设置标语失败',
              message: `为 ${sloganTarget} 设置标语失败：<br>未知错误：<br>${util.escapeHtml(error.message)}`,
            })
          }
        } else {
          const errorStr = String(error);
          this.$dialog.alert({
            title: '设置标语失败',
            message: `为 ${sloganTarget} 设置标语失败：<br>未知错误：<br><pre style="white-space:pre-wrap;word-wrap:break-word;">${util.escapeHtml(errorStr)}</pre>`,
          })
        }
      }
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos', 'account', 'celebBaseList']),
    ...mapGetters(['account'])
  }
}
</script>
