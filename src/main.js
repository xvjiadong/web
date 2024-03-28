import Vue from "vue";
import App from "./App.vue";
import "./registerServiceWorker";
import router from "./router";
import store from "./store";
import ElementUI from "element-ui";
import "./assets/font_4326048_bqm8mhudruq/iconfont.css";
import "element-ui/lib/theme-chalk/index.css";
Vue.config.productionTip = false;
import VueCompositionAPI from "@vue/composition-api";
import "@/util/axios.config";
Vue.use(VueCompositionAPI);
//import VueSocketIO from 'vue-socket.io'
//import SocketIO from 'socket.io-client'
/*const SOCKETIO = new VueSocketIO({
    debug: true, // true开启
    connection: SocketIO('http://127.0.0.1:5000'), // 里面写socket服务器地址
    options: {
        autoConnect: false // 关闭自动连接，一般是在用户登录过后才进行手动连接
    }
})*/
import Print from "vue-print-nb";
Vue.use(Print);
Vue.use(ElementUI);
//Vue.use(SOCKETIO)
new Vue({
    router,
    store,
    render: (h) => h(App),
}).$mount("#app");
