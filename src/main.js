import Vue from 'vue'
import App from './App.vue'
import './registerServiceWorker'
import router from './router'
import store from './store'
import ElementUI from 'element-ui';
import './assets/font_4326048_rzdbtdgikg/iconfont.css'
import 'element-ui/lib/theme-chalk/index.css';
Vue.config.productionTip = false
import VueCompositionAPI from '@vue/composition-api'
import '@/util/axios.config'
Vue.use(VueCompositionAPI)
import Print from 'vue-print-nb';
Vue.use(Print);
Vue.use(ElementUI);
new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
