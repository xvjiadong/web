import Vue from "vue";
import VueRouter from "vue-router";
import children from "@/router/addrouter";
import store from "@/store/index";
Vue.use(VueRouter);
const originalPush = VueRouter.prototype.push;
const originalReplace = VueRouter.prototype.replace;
// push
VueRouter.prototype.push = function push(location, onResolve, onReject) {
  if (onResolve || onReject)
    return originalPush.call(this, location, onResolve, onReject);
  return originalPush.call(this, location).catch((err) => err);
};
//replace
VueRouter.prototype.replace = function push(location, onResolve, onReject) {
  if (onResolve || onReject)
    return originalReplace.call(this, location, onResolve, onReject);
  return originalReplace.call(this, location).catch((err) => err);
};
const routes = [
  {
    path: "/",
    name: "dooropen",
    component: () =>
      import(/* webpackChunkName: "about" */ "../views/DoorOpen.vue"),
  },
  {
    path: "/login",
    name: "login",
    component: () =>
      import(/* webpackChunkName: "about" */ "../views/LoginIn.vue"),
  },
  {
    path: "/logon",
    name: "logon",
    component: () =>
      import(/* webpackChunkName: "about" */ "../views/LogOn.vue"),
  },
  {
    path: "/MainBox",
    name: "MainBox",
    component: () => import("../views/MainBox.vue"),
    children: [],
  },
  {
    path: "/company_enter",
    name: "company_enter",
    component: () => import("../views/CompanyEnter.vue"),
  },
  {
    path: "*",
    name: "NotFound",
    component: () => import("../views/NotFound.vue"),
    children: [],
  },
];

const router = new VueRouter({
  mode: "history",
  base: process.env.BASE_URL,
  routes,
});
const add = () => {
  //console.log(router);
  if (!router.getRoutes().find((item) => item.path === "/MainBox")) {
    router.addRoute({
      path: "/MainBox",
      name: "MainBox",
      component: () => import("../views/MainBox.vue"),
    });
  }
  if (store.state.user.identity === 0) {
    children.datalabelerrouter.forEach((item) => {
      router.addRoute("MainBox", item);
    });
  } else if (store.state.user.identity === 1) {
    children.projectmanagerrouter.forEach((item) => {
      router.addRoute("MainBox", item);
    });
  } else if (store.state.user.identity === 2) {
    children.platformmanagerrouter.forEach((item) => {
      router.addRoute("MainBox", item);
    });
  }
};
router.beforeEach((to, from, next) => {
  if (to.fullPath === "/" || to.fullPath === "/logon" || to.fullPath === "/login" || to.fullPath === "/company_enter") {
    next();
  } else {
    if (localStorage.getItem("token")) {
      if (!store.state.isadd) {
        const createRouter = () =>
          new VueRouter({
            mode: "history",
            routes: routes,
          });
        router.matcher = createRouter().matcher;
        add();
        store.commit("changeisadd", true);
        next({
          path: to.fullPath,
        });
      } else {
        if (
          to.name === "PicView" ||
          to.name === "PdfView" ||
          to.name === "ImageClassification" ||
          to.name === "TextClassification" ||
          to.name === "PicReview" ||
          to.name === "PdfReview" ||
          to.name === "TextPartReview" ||
          to.name === "PicPartReview" ||
          to.name === 'PicSegment'
        ) {
          next()
          /*if (
            Object.prototype.hasOwnProperty.call(to.query, "callType") &&
            Object.prototype.hasOwnProperty.call(to.query, "taskName") &&
            Object.prototype.hasOwnProperty.call(to.query, "projectName") &&
            Object.prototype.hasOwnProperty.call(to.query, "version")
          ) {
            if (to.name !== "PdfReview") {
              store.commit("clearisaddpdf")
            }
            next();
          } else {
            next({
              path: "/",
            });
          }*/
        } else {
          next();
        }
      }
    } else {
      next({
        path: "/",
      });
    }
  }
});
export default router;
