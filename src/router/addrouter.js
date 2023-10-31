const platformmanagerrouter = [
  {
    name: "CreareProject",
    path: "/CreateProject",
    component: () => import("../components/platformmanager/CreateProject.vue"),
  },
  {
    name: "PermissionChange",
    path: "/PermissionChange",
    component: () =>
      import("../components/platformmanager/PermissionChange.vue"),
  },
  {
    name: "PermissionReview",
    path: "/PermissionReview",
    component: () =>
      import("../components/platformmanager/PermissionReview.vue"),
  },
  {
    name: "PlatformRegulation",
    path: "/PlatformRegulation",
    component: () =>
      import("../components/platformmanager/PlatformRegulation.vue"),
  },
  {
    name: "ProjectList",
    path: "/ProjectList",
    component: () => import("../components/platformmanager/ProjectList.vue"),
  },
  {
    name: "ProjectSchedule",
    path: "/ProjectSchedule",
    component: () =>
      import("../components/platformmanager/ProjectSchedule.vue"),
  },
  {
    name: "TaskAnaysis",
    path: "/TaskAnaysis",
    component: () => import("../components/platformmanager/TaskAnaysis.vue"),
  },
  {
    name: "UserList",
    path: "/UserList",
    component: () => import("../components/platformmanager/UserList.vue"),
  },
  {
    name: "UserSchedule",
    path: "/UserSchedule",
    component: () => import("../components/platformmanager/UserSchedule.vue"),
  },
];
const projectmanagerrouter = [
  {
    name: "CreareProject",
    path: "/CreateProject",
    component: () => import("../components/projectmanager/CreateProject.vue"),
  },
  {
    name: "DataPublish",
    path: "/DataPublish",
    component: () => import("../components/projectmanager/DataPublish.vue"),
  },
  {
    name: "DataReview",
    path: "/DataReview",
    component: () => import("../components/projectmanager/DataReview.vue"),
  },
  {
    name: "LabelManager",
    path: "/LabelManager",
    component: () => import("../components/projectmanager/LabelManager.vue"),
  },
  {
    name: "MakeMark",
    path: "/MakeMark",
    component: () => import("../components/projectmanager/MakeMark.vue"),
  },
  {
    name: "ProjectAnaysis",
    path: "/ProjectAnaysis",
    component: () => import("../components/projectmanager/ProjectAnaysis.vue"),
  },
  {
    name: "ProjectList",
    path: "/ProjectList",
    component: () => import("../components/projectmanager/ProjectList.vue"),
  },
  {
    name: "TaskList",
    path: "/TaskList",
    component: () => import("../components/projectmanager/TaskList.vue"),
  },
  {
    name: "TaskSchedule",
    path: "/TaskSchedule",
    component: () => import("../components/projectmanager/TaskSchedule.vue"),
  },
  {
    path: "/PicView",
    name: "PicView",
    component: () =>
      import("../components/PicView.vue"),
  },
];
const datalabelerrouter = [
  {
    name: "MakeMark",
    path: "/MakeMark",
    component: () => import("../components/datalabeler/MakeMark.vue"),
  },
  {
    name: "MarkList",
    path: "/MarkList",
    component: () => import("../components/datalabeler/MarkList.vue"),
  },
  {
    name: "PermissionRequest",
    path: "/PermissionReuest",
    component: () => import("../components/datalabeler/PermissionRequest.vue"),
  },
  {
    path: "/PicView",
    name: "PicView",
    component: () =>
      import("../components/PicView.vue"),
  },
];
export default {
  platformmanagerrouter,
  projectmanagerrouter,
  datalabelerrouter,
};
