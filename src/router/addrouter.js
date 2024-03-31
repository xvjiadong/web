const platformmanagerrouter = [
  {
    name: "Adduser",
    path: "/adduser",
    component: () => import("../components/platformmanager/AddUser.vue"),
  },
  {
    name: "PersonCenter",
    path: "/PersonCenter",
    component: () => import("../views/PersonCenter.vue"),
  },
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
    path: "/pointview",
    name: "pointview",
    component: () => import("../components/PointView.vue"),
  },
  {
    path: "/polyline",
    name: "polyline",
    component: () => import("../components/PolyLine.vue"),
  },
  {
    name: "GenerateArea",
    path: "/GenerateArea",
    component: () => import("../components/projectmanager/GenerateArea.vue"),
  },
  {
    name: "TeamPlanning",
    path: "/TeamPlanning",
    component: () => import("../components/projectmanager/TeamPlanning.vue"),
  },
  {
    name: "RemainPic",
    path: "/RemainPic",
    component: () => import("../components/projectmanager/RemainPic.vue"),
  },
  {
    name: "PersonCenter",
    path: "/PersonCenter",
    component: () => import("../views/PersonCenter.vue"),
  },
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
    name: "editpic",
    path: "/EditPic",
    component: () => import("../components/projectmanager/EditPic.vue"),
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
    component: () => import("../components/PicView.vue"),
  },
  {
    path: "/ProjectDetail",
    name: "ProjectDetail",
    component: () => import("../components/projectmanager/ProjectDetail.vue"),
  },
  {
    path: "/InputFile",
    name: "InputFile",
    component: () => import("../components/projectmanager/InputFile.vue"),
  },
  {
    path: "/PdfView",
    name: "PdfView",
    component: () => import("../components/PdfView.vue"),
  },
  {
    path: "/TextClassification",
    name: "TextClassification",
    component: () => import("../components/TextClassification.vue"),
  },
  {
    path: "/ImageClassification",
    name: "ImageClassification",
    component: () => import("../components/ImageClassification.vue"),
  },
  {
    path: "/LabelDetail",
    name: "LabelDetail",
    component: () => import("../components/projectmanager/LabelDetail.vue"),
  },
  {
    path: "/PicPartReview",
    name: "PicPartReview",
    component: () => import("../components/PicPartReview.vue"),
  },
  {
    path: "/PicReview",
    name: "PicReview",
    component: () => import("../components/PicReview.vue"),
  },
  {
    path: "/PdfReview",
    name: "PdfReview",
    component: () => import("../components/PdfReview.vue"),
  },
  {
    path: "/segment",
    name: "segment",
    component: () => import("../components/PicSegment.vue"),
    children: [],
  },
  {
    path: "/TextPartReview",
    name: "TextPartReview",
    component: () => import("../components/TextPartReview.vue"),
  },
  {
    path: "/detect",
    name: "PicDetect",
    component: () => import("../components/PicDetect.vue"),
  },
  {
    path: "/entity",
    name: "entity",
    component: () => import("../components/EntityRecognize.vue"),
  },
  {
    path: "/keyandsummary",
    name: "keyandsummary",
    component: () => import("../components/KeyAndSummary.vue"),
  },
  {
    path: "/languageinference",
    name: "languageinference",
    component: () => import("../components/LanguageInference.vue"),
  }, {
    path: "/readview",
    name: "readview",
    component: () => import("../components/ReadView.vue"),
  },
  {
    path: "/publishdetail",
    name: "publishdetail",
    component: () => import("../components/projectmanager/PublishDetail.vue"),
  },
  {
    path: "/PdfView",
    name: "PdfView",
    component: () => import("../components/PdfView.vue"),
  },
];
const datalabelerrouter = [
  {
    path: "/languageinference",
    name: "languageinference",
    component: () => import("../components/LanguageInference.vue"),
  },
  {
    path: "/readview",
    name: "readview",
    component: () => import("../components/ReadView.vue"),
  },
  {
    path: "/pointview",
    name: "pointview",
    component: () => import("../components/PointView.vue"),
  },
  {
    path: "/polyline",
    name: "polyline",
    component: () => import("../components/PolyLine.vue"),
  },
  {
    path: "/languageinference",
    name: "languageinference",
    component: () => import("../components/LanguageInference.vue"),
  },
  {
    path: "/keyandsummary",
    name: "keyandsummary",
    component: () => import("../components/KeyAndSummary.vue"),
  },
  {
    path: "/entity",
    name: "entity",
    component: () => import("../components/EntityRecognize.vue"),
  },
  {
    path: "/detect",
    name: "PicDetect",
    component: () => import("../components/PicDetect.vue"),
  },
  {
    path: "/segment",
    name: "segment",
    component: () => import("../components/PicSegment.vue"),
    children: [],
  },
  {
    name: "PersonCenter",
    path: "/PersonCenter",
    component: () => import("../views/PersonCenter.vue"),
  },
  {
    name: "MakeMark",
    path: "/MakeMark",
    component: () => import("../components/datalabeler/MakeMark.vue"),
  },
  {
    name: "PermissionRequest",
    path: "/PermissionReuest",
    component: () => import("../components/datalabeler/PermissionRequest.vue"),
  },
  {
    path: "/PicView",
    name: "PicView",
    component: () => import("../components/PicView.vue"),
  },
  {
    path: "/PdfView",
    name: "PdfView",
    component: () => import("../components/PdfView.vue"),
  },
  {
    path: "/TextClassification",
    name: "TextClassification",
    component: () => import("../components/TextClassification.vue"),
  },
  {
    path: "/ImageClassification",
    name: "ImageClassification",
    component: () => import("../components/ImageClassification.vue"),
  },
];
const adminmanagerrouter = [
  {
    path: "/CheckMaterial",
    name: "checkmaterial",
    component: () => import("../components/adminmanager/CheckMaterial.vue"),
  },
  {
    path: "/CompanyManagement",
    name: "companymanagement",
    component: () => import("../components/adminmanager/CompanyManagement.vue"),
  },
]
export default {
  platformmanagerrouter,
  projectmanagerrouter,
  datalabelerrouter,
  adminmanagerrouter
};
