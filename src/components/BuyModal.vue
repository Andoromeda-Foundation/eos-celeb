<template>
  <form action="">
    <div class="modal-card" style="width: auto">
      <header class="modal-card-head">
        <p class="modal-card-title">购买 {{celebBaseList[priceInfo.id].name}}</p>
      </header>
      <section class="modal-card-body">
        <b-field label="价格">
          <b-field>
            <b-input
              v-bind:value="(getPrice() / 10000).toFixed(4)"
              readonly>
            </b-input>
            <p class="control">
              <a class="button is-static">
                EOS
              </a>
            </p>
          </b-field>
        </b-field>
      </section>
      <footer class="modal-card-foot">
        <button class="button is-rounded is-primary" @click="buy">使用 Scatter 支付</button>
        <button class="button is-rounded " type="button" @click="$parent.close()">取消</button>
      </footer>
    </div>
  </form>
</template>

<script>
import { mapState, mapGetters } from 'vuex'

const errorMessages = {
  'overdrawn balance': {
    message: '您的账户余额不足'
  },
  'no enough eos': {
    message: '有人比您抢先一步买下了该名人',
    refresh: true
  }
}

function escapeHtml (unsafe) {
  return unsafe
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;')
}

export default {
  name: 'BuyModal',
  props: ['priceInfo'],
  methods: {
    getPrice () {
      if (!this.priceInfo) {
        return 0
      } else {
        return this.priceInfo.price * 1.35
      }
    },
    async buy () {
      const { account, eos } = this
      const price = this.getPrice()
      const priceReadable = `${(price / 10000).toFixed(4)} EOS`
      const buyTarget = this.celebBaseList[this.priceInfo.id].name
      const memo = ['buy', String(this.priceInfo.id)]
      const referrer = localStorage.getItem('eos_celeb_referrer')
      if (referrer) {
        memo.push(referrer)
      }
      try {
        await eos.transfer(
          account.name,
          'crazytown.bp',
          priceReadable,
          `${memo.join(' ')}`,
          {
            authorization: [`${account.name}@${account.authority}`]
          }
        )
        this.$dialog.alert({
          title: '购买成功',
          message: `您已成功以 ${priceReadable} 购买 ${buyTarget}。`,
          onConfirm: () => {
            this.$parent.close()
            this.$store.dispatch('updateCeleb')
          }
        })
      } catch (error) {
        if (typeof error == 'object') {
          if (error.message.indexOf('User rejected the signature request') > -1) {
            this.$parent.close()
            this.$dialog.alert(`您在 Scatter 中取消了 ${buyTarget} 的购买。`);
          } else {
            this.$dialog.alert({
              title: '购买失败',
              message: `抱歉，以 ${priceReadable} 购买 ${buyTarget} 失败：<br>未知错误：<br>${escapeHtml(error.message)}`,
              onConfirm: () => {
                this.$parent.close()
                this.$store.dispatch('updateCeleb')
              }
            })
          }
        } else {
          const errorStr = String(error)
          for (let errorKeyword in errorMessages) {
            // Found a known error
            const errorProc = errorMessages[errorKeyword]
            if (errorStr.indexOf(errorKeyword) > -1) {
              this.$dialog.alert({
                title: '购买失败',
                message: `抱歉，以 ${priceReadable} 购买 ${buyTarget} 失败：<br>${errorProc.message}`,
                onConfirm: () => {
                  if (errorProc.refresh) {
                    this.$parent.close()
                    this.$store.dispatch('updateCeleb')
                  }
                }
              })
              return
            }
          }
          // Error: unknown error
          this.$dialog.alert({
            title: '购买失败',
            message: `抱歉，以 ${priceReadable} 购买 ${buyTarget} 失败：<br>未知错误：<br><pre style="white-space:pre-wrap;word-wrap:break-word;">${escapeHtml(errorStr)}</pre>`,
            onConfirm: () => {
              this.$parent.close()
              this.$store.dispatch('updateCeleb')
            }
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
