<template>
    <div class="celeb-list">
        <!-- {{celebs}} -->
        <div class="columns is-multiline">
            <div class="column is-3" v-for="celeb in celebs" :key="celeb.id">
                <div class="card">
                    <div class="card-image">
                        <figure class="image is-4by4">
                            <img :src="`https://eosheros.togetthere.cn/image/${celeb.id}.jpg`" class="is-rounded celeb-avatar" alt="Placeholder image">
                        </figure>
                    </div>
                    <div class="card-content">
                        <div class="media">
                        <!-- <div class="media-left">
                            <figure class="image is-48x48">
                            <img src="https://bulma.io/images/placeholders/96x96.png" alt="Placeholder image">
                            </figure>
                        </div> -->
                        <div class="media-content">
                            <p class="title is-4">{{celeb.name}}</p>
                            <p class="subtitle is-6"> {{celeb.price}} </p>
                        </div>
                        </div>

                        <div class="content">

                        <button class="button is-large" @click="buy(celeb)"> 以 {{celeb.price}} 购买 </button>
                        </div>
                    </div>
                    </div>
            </div>
        </div>
        <b-modal :active.sync="isComponentModalActive" has-modal-card>
            <buy-modal :person="currentBuy"></buy-modal>
        </b-modal>
    </div>
</template>

<script>
import { getCelebs } from '../blockchain/celeb'
import BuyModal from '@/components/BuyModal'
import {getTokenPrice} from '../blockchain/index'
export default {
  name: 'celeberties-list',
  components: {
    BuyModal
  },
  data: () => ({
    celebs: [],
    isComponentModalActive: false,
    currentBuy: -1
  }),
  async created () {
    this.celebs = await getCelebs();
    console.log(this.celebs)
      var tb = await getTokenPrice();
    console.log("ddddd");
    console.log(tb)
  },
  methods: {
    buy (celeb) {
      this.currentBuy = celeb
      this.isComponentModalActive = true
    }
  }
}
</script>

<style scoped>
.card {
  text-align: center;
}
.media-content * {
  text-align: center;
}
.image{
    height: 250px !important;
}
.card-content {
    padding-top: 2.5rem;
}
.image img {
    display: block;
    width: 90%;
    height: 90%;
    margin: auto;
}
.card:hover{
    transform: scale(1.05);
}
</style>
