<template>
  <div>
    <div class="celeb-list">
      <b-loading :is-full-page="false" :active.sync="dataIsLoading" :can-cancel="false"></b-loading>
      <div class="columns is-multiline">
        <div class="column is-3" v-for="celeb in celebBaseList" :key="celeb.id">
          <div class="celeb-card">
            <div class="celeb-image">
              <img :src="`https://eosheros.togetthere.cn/image/${celeb.id}.jpg`">
            </div>
            <div class="celeb-name"><p class="title">{{celeb.name}}</p></div>
            <div v-if="celebPriceList[celeb.id] !== undefined">
              <div class="celeb-price"><p class="subtitle has-text-info">{{ (celebPriceList[celeb.id].price * 1.35 / 10000).toFixed(4) }} EOS</p></div>
              <button class="button is-rounded is-light buy-button" @click="buy(celeb)"> 购买</button>
            </div>
            <div v-if="celebPriceList[celeb.id] === undefined">
              <div class="celeb-price"><p class="subtitle has-text-grey-light">Unavailable</p></div>
              <button class="button is-rounded is-light buy-button" disabled> 无法购买</button>
            </div>
          </div>
        </div>
      </div>
      <b-modal :active.sync="isDialogActive" has-modal-card>
        <buy-modal :celebInfo="currentBuy"></buy-modal>
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
  },
  data: () => ({
    isDialogActive: false,
    currentBuy: null
  }),
  methods: {
    buy (celeb) {
      this.currentBuy = celeb
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
