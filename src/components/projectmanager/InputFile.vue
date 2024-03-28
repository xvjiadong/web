<template>
  <div style="width: 95%; margin-top: 2%">
    <el-card class="box-card">
      <div slot="header" class="cardheader">
        <el-page-header @back="goBack" content="导入配置"> </el-page-header>
      </div>
      <el-form
        ref="form2"
        :model="dataset"
        label-width="110px"
        class="form"
        label-position="left"
      >
        <el-form-item label="导入项目版本" class="formitem">
          <i @click="change(page - 1)" class="el-icon-arrow-up turn"></i>
          {{ this.page }}
          <i @click="change(page + 1)" class="el-icon-arrow-down turn"></i>
          <el-select
            @change="projectchange"
            filterable
            size="mini"
            v-model="dataset.id"
            placeholder="请选择项目"
          >
            <el-option
              v-for="item in projectlist"
              :key="item.id"
              :label="item.name"
              :value="item.id"
            ></el-option>
          </el-select>
          <el-select
            filterable
            v-model="dataset.verName"
            size="mini"
            :disabled="dataset.id === ''"
            style="width: 22%; margin-left: 8px"
          >
            <el-option
              v-for="item in versionlist"
              :key="item.verName"
              :value="item.verName"
              :label="`${item.verName}-${item.callType}`"
            >
            </el-option>
          </el-select>
        </el-form-item>
        <el-form-item prop="ismarked" label="数据标注状态:" class="formitem">
          <el-radio v-model="dataset.ismarked" :label="true"
            >有标注信息</el-radio
          >
          <el-radio v-model="dataset.ismarked" :label="false"
            >无标注信息</el-radio
          >
        </el-form-item>
        <el-form-item prop="inputway" label="导入方式:" class="formitem">
          <el-select filterable="" v-model="dataset.inputway" size="small">
            <el-option
              v-for="item in input"
              :key="item.value"
              :value="item.value"
              :label="item.label"
            >
            </el-option>
          </el-select>
          <el-select
            v-if="dataset.inputway === '本地导入'"
            filterable=""
            v-model="dataset.inputway2"
            size="small"
          >
            <el-option
              v-for="item in uploadway"
              :key="item.value"
              :value="item.value"
              :label="item.label"
            >
            </el-option>
          </el-select>
        </el-form-item>
        <el-form-item
          v-if="dataset.inputway2 !== '' && dataset.inputway === '本地导入'"
          prop="file"
          :label="uploadlabel"
          class="formitem version"
        >
          <el-upload
            ref="upload"
            :file-list="dataset.file"
            drag
            multiple
            action=""
            :auto-upload="false"
            :accept="filetype"
            :on-change="filecheck"
            :on-success="uploadsuccess"
            :on-error="uploaderror"
            :list-type="listType"
            :on-remove="uploadremove"
          >
            <div slot="trigger">
              <i class="el-icon-upload"></i>
              <div class="el-upload__text">
                将文件拖到此处，或<em>点击上传</em><br />
                可接受文件类型:{{ filetype }}
              </div>
            </div>
            <div class="el-upload__tip" slot="tip">
              文件大小限制在14MB内，请确保文件格式正确
            </div>
          </el-upload>
        </el-form-item>
        <el-form-item
          v-if="
            dataset.inputway === '分享链接导入' ||
            dataset.inputway === '平台已有数据集'
          "
          :label="uploadlabel"
          class="formitem"
          prop="link"
        >
          <el-input
            style="width: 60%"
            v-if="dataset.inputway === '分享链接导入'"
            size="small"
            v-model="dataset.link"
            placeholder="请输入分享链接"
          ></el-input>
          <el-select
            v-if="dataset.inputway === '平台已有数据集'"
            size="small"
            v-model="dataset.link"
            placeholder="请选择数据集"
          >
            <el-option
              v-for="item in addlink"
              :key="item.value"
              :value="item.value"
            ></el-option>
          </el-select>
        </el-form-item>
        <el-form-item
          class="formitem"
          :class="{ pic: listType === 'picture-card' }"
        >
          <el-button size="small" type="primary" @click="complete2"
            >导入数据集</el-button
          >
          <el-button @click="jump">取消</el-button>
        </el-form-item>
      </el-form>
    </el-card>
  </div>
</template>
<script>
import axios from "axios";
export default {
  data() {
    return {
      dataset: {
        dataType: "",
        id: "",
        verName: "",
        ismarked: false,
        inputway: "",
        inputway2: "",
        file: [],
        link: "",
      },
      input: [
        { value: "本地导入", label: "本地导入" },
        { value: "平台已有数据集", label: "平台已有数据集" },
        { value: "分享链接导入", label: "分享链接导入" },
      ],
      addlink: [{ value: "9878" }],
      projectlist: [],
      page: 1,
      pages: 0,
    };
  },
  computed: {
    versionlist() {
      console.log(this.dataset.id);
      if (this.dataset.id !== "") {
        return this.projectlist.filter((item) => {
          return item.id == this.dataset.id;
        })[0].versions;
      }
      return [];
    },
    uploadway() {
      let a = [
        { value: "上传压缩包", label: "上传压缩包" },
        { value: "上传PDF", label: "上传PDF" },
        { value: "上传docx", label: "上传docx" },
        { value: "上传txt", label: "上传txt" },
      ];
      let b = [
        { value: "上传压缩包", label: "上传压缩包" },
        { value: "上传图片", label: "上传图片" },
      ];
      if (this.dataset.dataType === "文本") {
        return a;
      } else if (this.dataset.dataType === "图像") {
        if (this.dataset.ismarked) {
          return [{ value: "上传压缩包", label: "上传压缩包" }];
        }
        return b;
      }
      return [];
    },
    uploadlabel() {
      if (this.dataset.inputway === "平台已有数据集") {
        return "选择数据集:";
      } else if (this.dataset.inputway === "分享链接导入") {
        return "链接地址:";
      } else if (
        this.dataset.inputway2 === "上传压缩包" ||
        this.dataset.ismarked
      ) {
        return "上传压缩包:";
      } else if (this.dataset.inputway2 === "上传PDF") {
        return "上传PDF:";
      } else if (this.dataset.inputway2 === "上传docx") {
        return "上传docx:";
      } else if (this.dataset.inputway2 === "上传图片") {
        return "上传图片:";
      } else if (this.dataset.inputway2 === "上传txt") {
        return "上传txt:";
      }
      return "";
    },
    filetype() {
      if (this.uploadlabel === "上传压缩包:") {
        return ".zip,.rar,.tar.gz";
      } else if (this.uploadlabel === "上传PDF:") {
        return ".pdf";
      } else if (this.uploadlabel === "上传docx:") {
        return ".docx,.doc";
      } else if (this.uploadlabel === "上传图片:") {
        return ".bmp,.jpg,.jpeg,.png,.JPEG";
      } else if (this.uploadlabel === "上传txt:") {
        return ".txt";
      }
      return "";
    },
    listType() {
      if (this.uploadlabel === "上传图片:") {
        return "picture-card";
      }
      return "text";
    },
  },
  watch: {
    "dataset.inputway2": {
      handler() {
        if (this.dataset.file.length > 0) {
          //this.$refs.upload.clearFiles()
          this.dataset.file = [];
        }
      },
    },
    "dataset.inputway": {
      handler() {
        //console.log(newvalue, oldvalue);
        if (this.dataset.file.length > 0) {
          //this.$refs.upload.clearFiles()
          this.dataset.file = [];
        }
      },
    },
    "dataset.ismarked": {
      handler() {
        this.dataset.inputway = "";
        this.dataset.inputway2 = "";
        this.dataset.file = [];
        //this.$refs.upload.clearFiles()
      },
    },
    "dataset.datatype": {
      handler() {
        this.dataset.marktype = "";
      },
    },
  },
  methods: {
    projectchange(val) {
      let a = this.projectlist.filter((item) => {
        return item.id == val;
      });
      this.dataset.dataType = a[0].dataType;
    },
    change(num) {
      if (num === 0) {
        this.$message.error("已经是第一页了");
        return;
      } else if (num > this.pages) {
        this.$message.error("已经是最后一页了");
        return;
      }
      this.page = num;
      this.getdata(this.page);
    },
    goBack() {
      this.$router.push("/ProjectList");
    },
    complete2() {
      console.log(this.dataset);
      let file = new FormData();
      this.dataset.file.forEach((item) => {
        file.append("file", item.raw);
      });
      file.append("id", this.dataset.id);
      file.append("version", this.dataset.verName);
      console.log(file.getAll("file"), file.get("id"));
      if (this.dataset.inputway2 === "上传图片") {
        axios
          .post("http://120.26.142.114:10010/items/image", file, {
            headers: { "Content-Type": "multipart/form-data" },
          })
          .then((res2) => {
            console.log(res2.data);
            setTimeout(() => {
              this.active += 1;
              this.$router.push("/Projectlist");
            }, 1000);
          });
      } else if (this.dataset.inputway2 === "上传docx") {
        axios
          .post("http://120.26.142.114:10010/items/docx", file, {
            headers: { "Content-Type": "multipart/form-data" },
          })
          .then((res2) => {
            console.log(res2.data);
            setTimeout(() => {
              this.active += 1;
              this.$router.push("/Projectlist");
            }, 1000);
          });
      } else if (this.dataset.inputway2 === "上传PDF") {
        axios
          .post("http://120.26.142.114:10010/items/pdf", file, {
            headers: { "Content-Type": "multipart/form-data" },
          })
          .then((res2) => {
            console.log(res2.data);
            setTimeout(() => {
              this.active += 1;
              this.$router.push("/Projectlist");
            }, 1000);
          });
      } else if (this.dataset.inputway2 === "上传txt") {
        axios
          .post("http://120.26.142.114:10010/items/txt", file, {
            headers: { "Content-Type": "multipart/form-data" },
          })
          .then((res2) => {
            console.log(res2.data);
            this.$message({ type: "success", message: "创建项目成功" });
            setTimeout(() => {
              this.active += 1;
              this.$router.push("/Projectlist");
            }, 1000);
          });
      }
    },
    jump() {
      this.$router.push("/ProjectList");
    },
    filecheck(file) {
      if (file.size / 1024 / 1024 > 14) {
        this.$message({
          type: "warning",
          message: file.name + "上传文件大小不能超过14MB",
        });
        this.$refs.upload.onRemove(file);
        //console.log(this.dataset.file);
      } else if (
        !this.filetype.includes(
          file.name.split(".")[file.name.split(".").length - 1]
        )
      ) {
        this.$message({
          type: "warning",
          message: file.name + "不符合上传格式要求",
        });
        this.$refs.upload.onRemove(file);
      } else {
        console.log(file.raw);
        this.dataset.file.push(file);
        //console.log(this.dataset.file);
      }
    },
    uploadsuccess() {
      this.dataset.file = [];
    },
    uploaderror() {},
    uploadremove(file) {
      console.log(file);
      this.dataset.file = this.dataset.file.filter((item) => {
        return item.name !== file.name;
      });
    },
    getdata(page) {
      axios
        .get(`http://120.26.142.114:10010/items?current=${page}&pageSize=10`)
        .then((res) => {
          this.projectlist = res.data.data.list;
          this.pages = Math.floor((res.data.data.total - 1) / 10) + 1;
          console.log(this.projectlist);
          this.dataset = {
            dataType: "",
            id: "",
            verName: "",
            ismarked: false,
            inputway: "",
            inputway2: "",
            file: [],
            link: "",
          };
        })
        .catch((e) => {
          console.log(e);
        });
    },
  },
  mounted() {
    console.log(this.$route.query);
    this.page = this.$route.query.page - 0;
    //let a = this.$route.query
    this.getdata(this.page);
  },
};
</script>
<style scoped>
.box-card {
  width: 100%;
  margin-left: 1%;
  height: 600px;
}

.cardheader {
  display: flex;
  justify-content: left;
  padding-left: 15px;
  align-items: center;
  font-size: 25px;
}

.form {
  font-size: 30px;
  padding: 15px;
}

.formitem {
  width: 60%;
  text-align: left;
}

/deep/.el-upload-list {
  margin: 0;
  padding: 0;
  list-style: none;
  position: absolute;
  top: -74%;
  left: 78%;
  height: 220%;
  width: 100%;
  overflow-y: scroll;
}

/deep/.el-upload-list--picture .el-upload-list__item {
  z-index: 0;
  background-color: #fff;
  border: 1px solid #c0ccda;
  border-radius: 6px;
  box-sizing: border-box;
  margin-top: 10px;
  margin-left: 10px;
  margin-bottom: 10px;
  padding: 10px 10px 10px 90px;
  height: 35%;
  float: left;
  width: 35%;
}

/deep/.el-upload--picture-card {
  background-color: #fbfdff;
  border: 1px dashed #c0ccda;
  border-radius: 6px;
  box-sizing: border-box;
  width: 148px;
  height: 148px;
  vertical-align: top;
  line-height: 38px;
}

.pic {
  margin-top: 80px;
}

.turn {
  cursor: pointer;
  font-size: 20px;
}

.turn:hover {
  color: rgb(36, 104, 255);
}
</style>
