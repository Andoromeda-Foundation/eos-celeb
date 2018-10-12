<template>
  <div>
    <div class="celeb-list">
      <b-loading :is-full-page="false" :active.sync="dataIsLoading" :can-cancel="false"></b-loading>
      <div class="columns is-multiline">
        <div class="column is-3" v-for="priceInfo in celebPriceList" :key="priceInfo.id" v-if="celebBaseList[priceInfo.id]">
          <div class="celeb-card">
            <div class="celeb-image">
              <img :src="`https://eosheros.togetthere.cn/image/${celebBaseList[priceInfo.id].id}.jpg`">
            </div>
            <div class="celeb-name"><p class="title">{{celebBaseList[priceInfo.id].name}}</p></div>
            <div class="celeb-price"><p class="subtitle has-text-info">{{ (priceInfo.price * 1.35 / 10000).toFixed(4) }} EOS</p></div>
            <button class="button is-rounded is-light buy-button" v-if="account === null" disabled>登录后购买</button>
            <button class="button is-rounded is-light buy-button" v-if="account !== null" @click="buy(priceInfo)">购买</button>
          </div>
        </div>
      </div>
      <b-modal :active.sync="isDialogActive" has-modal-card>
        <buy-modal :priceInfo="currentBuy"></buy-modal>
      </b-modal>
    </div>
  </div>
</template>

<script>
import { mapState, mapGetters } from 'vuex'
import BuyModal from '@/components/BuyModal'
export default {
  name: 'celeberties-list',
  components: {
    BuyModal
  },
  computed: {
    ...mapState(['celebBaseList', 'celebPriceList', 'dataIsLoading']),
    ...mapGetters(['account'])
  },
  data: () => ({
    isDialogActive: false,
    currentBuy: null
  }),
  methods: {
    buy (priceInfo) {
      this.currentBuy = priceInfo
      this.isDialogActive = true
    }
  }
}
</script>

<style scoped>
.celeb-list {
  min-height: 500px;
}

.celeb-card {
  border-radius: 10px;
  background: #FFF;
  text-align: center;
  padding: 2rem;
  margin: 0.5rem;
  box-shadow: 0 10px 40px rgba(0,0,0,0.03), 0 10px 15px rgba(0,0,0,0.04);
  transition: box-shadow .2s ease-out;
}

.celeb-card:hover {
  box-shadow: 0 20px 40px rgba(0,0,0,0.09), 0 15px 30px rgba(0,0,0,0.09);
}

.celeb-card .celeb-image img {
  border: 0;
  width: 200px;
  height: 200px;
  border-radius: 50%;
  overflow: hidden;
  margin-bottom: 1rem;
}

.celeb-card .celeb-name {
  margin: 0.5rem 0;
}

.celeb-card .celeb-price {
  margin: 0.5rem 0;
}

.celeb-card .buy-button {
  min-width: 150px;
  margin: 1rem 0;
  padding-left: 1.5rem;
  padding-right: 1.5rem;
}
</style>
