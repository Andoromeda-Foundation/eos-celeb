<template>
  <form action="">
    <div class="modal-card" style="width: auto">
      <header class="modal-card-head">
        <p class="modal-card-title">购买 {{celebInfo.name}}</p>
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
export default {
  name: 'BuyModal',
  props: ['celebInfo'],
  methods: {
    getPrice () {
      if (!this.celebInfo) {
        return 0;
      } else {
        return this.celebPriceList[this.celebInfo.id].price * 1.35;
      }
    },
    async buy () {
      const { account, eos } = this
      const price = this.getPrice()
      const priceReadable = `${(price / 10000).toFixed(4)} EOS`
      const memo = `buy ${this.celebInfo.id}`
      try {
        await eos.transfer(
          account.name,
          'crazytown.bp',
          priceReadable,
          `${memo}`,
          {
            authorization: [`${account.name}@${account.authority}`]
          }
        )
        this.$dialog.alert({
          title: '购买成功',
          message: `您已成功以 ${priceReadable} EOS 购买 ${this.celebInfo.name}。`
        });
      } catch (error) {
        this.$dialog.alert({
          title: '购买失败',
          message: `抱歉，以 ${priceReadable} EOS 购买 ${this.celebInfo.name} 失败。`
        });
      }
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos', 'account', 'celebPriceList']),
    ...mapGetters(['account'])
  }
}
</script>
