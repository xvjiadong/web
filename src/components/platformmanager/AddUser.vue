<template>
    <div style="display: flex;width: 100%;height: 90%;">

        <div style="width: 30%;height: 90%;display: flex;align-items: center;padding-left: 20px;">
            <div>
                <el-upload ref="upload" :limit="1" class="upload-demo" drag action="" :auto-upload="false"
                    :accept="'.xlsx'" :file-list="adduser.files" :on-change="filecheck" :on-success="uploadsuccess"
                    :on-error="uploaderror" :on-remove="uploadremove">
                    <i class="el-icon-upload"></i>
                    <div class="el-upload__text">将文件拖到此处，或<em>点击上传</em></div>
                    <div class="el-upload__tip" slot="tip">只能上传excel文件，上传文件规范见
                        <a download="上传文件示例.xlsx" href="../../../示例文件/导入员工.xlsx">示例</a>
                    </div>
                </el-upload>
                <el-button @click="uploaduser" type="primary" size="small"
                    style="font-size: 20px;margin-top: 15px;">导入员工</el-button>
                <div style="margin-top: 15px;">
                    <a v-if="!success" :download="url.split('/')[url.split('/').length - 1]" :href="url">
                        下载员工账号数据
                    </a>
                </div>
            </div>
        </div>
        <div style="height: auto;overflow-y: auto;width: 70%;">
            <el-table :stripe="true" :border="true" v-if="excelData.length > 0" :data="excelData">
                <el-table-column prop="姓名" label="姓名"></el-table-column>
                <el-table-column prop="身份" label="身份"></el-table-column>
                <el-table-column prop="邮箱" label="邮箱"></el-table-column>
                <el-table-column prop="手机号" label="手机号"></el-table-column>
            </el-table>
        </div>
    </div>
</template>

<script>
import * as xlsx from 'xlsx';
export default {
    data() {
        return {
            url: "",
            success: false,
            adduser: {
                companyNumber: "",
                files: []
            },
            excelData: []
        }
    },
    methods: {
        uploaduser() {
            if (this.files.length == 0) {
                this.$message.warning("请上传规范员工表格")
            } else {
                /*axios.post("")
                    .then(res => {
                        console.log(res);
                    })
                    .catch(e => {
                        console.log(e);
                    })*/
            }
        },
        filecheck(file) {
            this.adduser.files.push(file.raw)
            const reader = new FileReader();
            reader.onload = (e) => {
                const data = new Uint8Array(e.target.result);
                const workbook = xlsx.read(data, { type: 'array' });
                const sheetName = workbook.SheetNames[0];
                const worksheet = workbook.Sheets[sheetName];
                const excelData = xlsx.utils.sheet_to_json(worksheet, { header: 1 });
                if (excelData[0][0] !== '姓名' || excelData[0][1] !== '身份' || excelData[0][2] !== '邮箱' || excelData[0][3] !== '手机号') {
                    this.$message.warning("文件格式不正确，请重新上传")
                    this.$refs.upload.onRemove(file)
                    return
                }
                for (let i = 1; i < excelData.length; i++) {
                    this.excelData.push({ '姓名': excelData[i][0], '身份': excelData[i][1], '邮箱': excelData[i][2], '手机号': excelData[i][3] })
                }
                console.log(this.excelData);
            };
            reader.readAsArrayBuffer(file.raw);
        },
        uploadsuccess() {
            this.adduser.files = []
            console.log("成功");
        },
        uploaderror() {
            console.log(xlsx);
        },
        uploadremove(file) {
            console.log(file);
            this.adduser.files = this.adduser.files.filter(item => {
                return item.name !== file.name
            })
            this.excelData = []
        },
    }
}
</script>

<style scoped>
/deep/.el-table .el-table__cell {
    padding: 12px 0;
    min-width: 0;
    box-sizing: border-box;
    text-overflow: ellipsis;
    vertical-align: middle;
    position: relative;
    text-align: center;
}
</style>