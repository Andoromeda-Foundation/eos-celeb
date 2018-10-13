<template>
  <div class="leaderboard content">
    <b-table :data="generateLeaderboard()">
      <template slot-scope="props">
        <b-table-column :label="$t('leaderboard_label_rank')">
          #{{ props.index + 1 }}
        </b-table-column>
        <b-table-column field="name" :label="$t('leaderboard_label_name')">
          {{ props.row.name }}
        </b-table-column>
        <b-table-column field="totalAssetValue" :label="$t('leaderboard_label_total_value')">
          {{ (props.row.totalAssetValue / 10000).toFixed(4) }} EOS
        </b-table-column>
        <b-table-column field="cards" :label="$t('leaderboard_label_celeb_count')">
          {{ props.row.cards }}
        </b-table-column>
        <b-table-column :label="$t('leaderboard_label_celeb_top')">
          <div class="celeb-item" :key="item.id" v-for="item in props.row.assets">
            <b-taglist attached>
                <b-tag size="is-medium" type="is-dark">{{celebBaseList[item.id].name}}</b-tag>
                <b-tag size="is-medium" :type="item.category">{{(item.price/10000).toFixed(4)}} EOS</b-tag>
                <b-tag size="is-medium" type="is-light" v-if="item.slogan">{{item.slogan}}</b-tag>
            </b-taglist>
          </div>
        </b-table-column>
      </template>
    </b-table>
  </div>
</template>

<script>
import { mapState, mapGetters } from 'vuex'
import orderBy from 'lodash.orderby'

export default {
  name: 'leaderboard',
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
  }),
  methods: {
    generateLeaderboard () {
      const mostValuedCeleb = orderBy(this.celebPriceList, ['price'], ['desc'])
      const categories = {
        'is-danger': {},
        'is-warning': {}
      }
      for (let i = 0; i < 10; i++) {
        categories['is-danger'][mostValuedCeleb[i].id] = true
      }
      for (let i = 10; i < 25; i++) {
        categories['is-warning'][mostValuedCeleb[i].id] = true
      }

      let infoPerOwner = {}
      this.celebPriceList.forEach(item => {
        if (this.celebBaseList[item.id] === undefined) {
          return
        }
        if (infoPerOwner[item.owner] === undefined) {
          infoPerOwner[item.owner] = {
            cards: 0,
            assets: [],
            totalAssetValue: 0
          }
        }
        let infoItem = infoPerOwner[item.owner]
        infoItem.cards += 1
        infoItem.assets.push(item)
        infoItem.totalAssetValue += item.price
      })
      let infoList = []
      for (let name in infoPerOwner) {
        infoList.push({
          name,
          ...infoPerOwner[name],
          assets: orderBy(infoPerOwner[name].assets, ['price', 'id'], ['desc', 'asc']).slice(0, 5).map(asset => {
            let cloned = { ...asset }
            cloned.category = 'is-info'
            for (let kind in categories) {
              if (categories[kind][cloned.id]) {
                cloned.category = kind
                break
              }
            }
            return cloned
          })
        })
      }
      return orderBy(infoList, ['totalAssetValue', 'cards'], ['desc', 'desc']).slice(0, 20)
    }
  }
}
</script>

<style scoped>
.celeb-item {
  margin: 0.5rem 0;
}
</style>
