<template>
  <div>
    <div class="container global-info">
      <nav class="level" v-if="globalInfo">
        <div class="level-item has-text-centered">
          <div>
            <p class="heading">奖池大小</p>
            <p class="title">{{ (globalInfo.pool / 10000).toFixed(4) }} EOS</p>
          </div>
        </div>
        <div class="level-item has-text-centered">
          <div>
            <p class="heading">结束倒计时</p>
            <p class="title">{{ globalCountdown }}</p>
          </div>
        </div>
        <div class="level-item has-text-centered">
          <div>
            <p class="heading">最后购买者</p>
            <p class="title" :title="globalInfo.last">{{ truncate(globalInfo.last) }}</p>
          </div>
        </div>
        <div class="level-item has-text-centered">
          <b-field label="排序方式">
            <b-select rounded v-model="orderBy">
              <option value="default">默认</option>
              <option value="asc">价格从低到高</option>
              <option value="desc">价格从高到低</option>
            </b-select>
          </b-field>
        </div>
      </nav>
    </div>
    <div class="celeb-list">
      <b-loading :is-full-page="false" :active.sync="dataIsLoading" :can-cancel="false"></b-loading>
      <div class="columns is-multiline">
        <div class="column is-3" v-for="priceInfo in orderList(celebPriceList)" :key="priceInfo.id" v-if="celebBaseList[priceInfo.id]">
          <div class="celeb-card">
            <div class="celeb-image">
              <img :src="`https://eosheros.togetthere.cn/image/${celebBaseList[priceInfo.id].id}.jpg`">
            </div>
            <div class="celeb-name"><p class="title">{{celebBaseList[priceInfo.id].name}}</p></div>
            <div class="celeb-holder">
              <p class="holder">持有者: {{priceInfo.owner}}</p>
              <p class="slogan" v-if="priceInfo.slogan">标语: {{priceInfo.slogan}}</p>
            </div>
            <div class="celeb-price"><p class="is-size-4 has-text-info">{{ (priceInfo.price * 1.35 / 10000).toFixed(4) }} EOS</p></div>
            <button class="button is-rounded is-light buy-button" v-if="account === null" disabled>登录后购买</button>
            <button class="button is-rounded is-light buy-button" v-if="account !== null && priceInfo.owner != account.name" @click="buy(priceInfo)">购买</button>
            <button class="button is-rounded is-primary buy-button" v-if="account !== null && priceInfo.owner == account.name" @click="edit(priceInfo)">修改标语</button>
          </div>
        </div>
      </div>
      <b-modal :active.sync="isBuyDialogActive" has-modal-card>
        <buy-modal :priceInfo="currentBuy"></buy-modal>
      </b-modal>
      <b-modal :active.sync="isEditSloganDialogActive" has-modal-card>
        <edit-slogan-modal :priceInfo="currentBuy"></edit-slogan-modal>
      </b-modal>
    </div>
  </div>
</template>

<script>
import { mapState, mapGetters } from 'vuex'
import BuyModal from '@/components/BuyModal'
import EditSloganModal from '@/components/EditSloganModal'
import orderBy from 'lodash.orderby'

function padTimeZero (str) {
  let t = '00' + str
  return t.slice(t.length - 2, t.length)
}

export default {
  name: 'celeberties-list',
  components: {
    BuyModal,
    EditSloganModal
  },
  computed: {
    ...mapState([
      'celebBaseList',
      'celebPriceList',
      'dataIsLoading',
      'globalInfo'
    ]),
    ...mapGetters(['account'])
  },
  data: () => ({
    isBuyDialogActive: false,
    isEditSloganDialogActive: false,
    currentBuy: null,
    globalCountdown: '00:00:00',
    orderBy: 'default'
  }),
  created: function () {
    if (this.$route.params.account) {
      console.log('Referrer: %s', this.$route.params.account)
      localStorage.setItem('eos_celeb_referrer', this.$route.params.account)
    }

    this.countdownUpdater = setInterval(() => {
      if (this.globalInfo != null) {
        const currentTimestamp = ~~(Date.now() / 1000)
        if (currentTimestamp >= this.globalInfo.ed) {
          this.globalCountdown = '已结束'
        } else {
          let remaining = this.globalInfo.ed - currentTimestamp
          const seconds = remaining % 60
          remaining = ~~(remaining / 60)
          const minutes = remaining % 60
          remaining = ~~(remaining / 60)
          const hours = remaining
          this.globalCountdown = `${padTimeZero(hours)}:${padTimeZero(
            minutes
          )}:${padTimeZero(seconds)}`
        }
      }
    }, 1000)
  },
  destroyed: function () {
    if (this.countdownUpdater) {
      clearInterval(this.countdownUpdater)
    }
  },
  methods: {
    buy (priceInfo) {
      this.currentBuy = priceInfo
      this.isBuyDialogActive = true
    },
    edit (priceInfo) {
      this.currentBuy = priceInfo
      this.isEditSloganDialogActive = true
    },
    orderList (list) {
      if (this.orderBy === 'asc') {
        return orderBy(list, ['price', 'id'], ['asc', 'asc'])
      } else if (this.orderBy === 'desc') {
        return orderBy(list, ['price', 'id'], ['desc', 'asc'])
      } else {
        return list
      }
    },
    truncate (str) {
      try {
        if (str.length > 10) {
          return str.substr(0, 10) + '...'
        } else {
          return str
        }
      } catch (e) {
        return str
      }
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
  background: #fff;
  text-align: center;
  padding: 2rem;
  margin: 0.5rem;
  box-shadow: 0 10px 40px rgba(0, 0, 0, 0.03), 0 10px 15px rgba(0, 0, 0, 0.04);
  transition: box-shadow 0.2s ease-out;
}

.celeb-card:hover {
  box-shadow: 0 20px 40px rgba(0, 0, 0, 0.09), 0 15px 30px rgba(0, 0, 0, 0.09);
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

.celeb-card .celeb-holder {
  margin: 1rem 0;
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
