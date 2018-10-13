<template>
  <form action="">
    <div class="modal-card" style="min-width: 500px; width: auto">
      <header class="modal-card-head">
        <p class="modal-card-title">{{$t('invite_modal_title')}}</p>
      </header>
      <section class="modal-card-body">
        <b-field :label="$t('invite_modal_label')">
          <b-field>
            <b-input
              id="refLink"
              v-bind:value="getRefer()"
              readonly
              expanded>
            </b-input>
            <p class="control">
              <a class="button is-primary" @click="copy">
                {{$t('invite_modal_copy')}}
              </a>
            </p>
          </b-field>
        </b-field>
      </section>
      <footer class="modal-card-foot">
        <button class="button is-rounded" @click="$parent.close()">{{$t('invite_modal_close')}}</button>
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
          message: this.$t('invite_modal_copy_success'),
          type: 'is-success',
          duration: 3000,
          position: 'is-bottom',
          queue: false
        })
        this.$parent.close()
      }, () => {
        this.$toast.open({
          message: this.$t('invite_modal_copy_fail'),
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
