<template>
    <form action="">
                <div class="modal-card" style="width: auto">
                    <header class="modal-card-head">
                        <p class="modal-card-title">购买 {{person.name}}</p>
                    </header>
                    <section class="modal-card-body">
                        <b-field label="Price">
                            <b-input
                                v-model="price"
                                placeholder="Your Price"
                                required>
                            </b-input>
                        </b-field>
                    </section>
                    <footer class="modal-card-foot">
                        <button class="button" type="button" @click="$parent.close()">取消</button>
                        <button class="button is-primary" @click="buy">使用 Scatter 支付</button>
                    </footer>
                </div>
            </form>
</template>

<script>
import { mapState, mapGetters } from 'vuex'
export default {
  name: 'BuyModal',
  props: ['person'],
  data: () => ({
    price: '0.0000 EOS'
  }),
  methods: {
    async buy () {
      const { account, eos, price } = this
      const memo = 'buy' // edit memo if needed
      try {
        await eos.transfer(
          account.name,
          'yabukinanako',
          price,
          `${memo}`,
          {
            authorization: [`${account.name}@${account.authority}`]
          }
        )
        this.$dialog.alert('购买成功')
      } catch (error) {
        this.$dialog.alert('购买失败')
      }
    }
  },
  computed: {
    ...mapState(['identity', 'scatter', 'eos', 'account']),
    ...mapGetters(['account'])
  }
}
</script>
