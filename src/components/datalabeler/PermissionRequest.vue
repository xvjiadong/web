<template>
    <div style="margin-top: 25px;">
        <!--
        1.个人信息(什么公司、职位)
        2.申请原因(数据集用途、数据来源)
        3.证明材料(部门证明材料、上传数据样例)
        4.勾选协议
        -->
        <el-card class="box-card">
            <div slot="header" class="cardheader">
                <span>申请材料</span>
            </div>
            <el-form ref="form" :model="req" :rules="reqrule" label-width="100px" class="form">
                <el-form-item prop="company" label="所在单位" class="formitem">
                    <el-input style="width: 60%;" size="mini" v-model="req.company" placeholder="所在单位"></el-input>
                </el-form-item>
                <el-form-item prop="position" label="现居职位" class="formitem">
                    <el-input v-model="req.position" style="width: 60%;" size="mini" placeholder="请填写您现居职位"></el-input>
                </el-form-item>
                <el-form-item prop="reason" label="申请原因" class="formitem">
                    <el-input placeholder="请填写申请原因，原因至少要包括数据集用途、数据来源，否则不予通过" type="textarea" v-model="req.reason"
                        maxlength="200" show-word-limit></el-input>
                </el-form-item>
                <el-form-item prop="evidence" label="证明材料" class="formitem">
                    <el-upload ref="upload" accept=".pdf" action="" :file-list="req.evidence" :limit="10"
                        v-model="req.evidence" draggable style="text-align: left;" :auto-upload="false"
                        :on-change="uploadchange" :on-remove="uploadremove">
                        <el-button size="mini" style="border: 1px solid rgb(36,104,242);color: rgb(36,104,242);">
                            <i class="el-icon-upload"></i>点击上传</el-button>
                        <span slot="tip" class="el-upload__tip"
                            style="margin-left: 8px;">请上传数据样例和部门证明材料(支持20M以内的pdf文件)</span>
                    </el-upload>
                </el-form-item>
                <el-form-item class="formitem">
                    <el-checkbox :disabled="agreedisabled" v-model="req.agree"></el-checkbox>
                    <span style="cursor: pointer;text-decoration: underline;color: rgb(36,104,242);"
                        @click="centerDialogVisible = true">请查阅后勾选协议</span>
                </el-form-item>
                <el-form-item class="formitem">
                    <el-button type="primary" size="mini" @click="submit">确认申请</el-button>
                </el-form-item>
            </el-form>
        </el-card>

        <el-dialog title="数据协议" :visible.sync="centerDialogVisible" width="40%" @close="agreedisabled = false">
            <div style="height: 200px;overflow-y: auto;word-break: keep-all;text-align: left;">
                数据标注平台的数据协议

                数据所有权：数据的所有权归属于数据提供方，数据标注平台在使用数据时应遵守相应的法律法规。

                数据保密：数据标注平台应对数据提供方的数据进行保密，不得将数据泄露给任何第三方。

                数据使用目的：数据标注平台只能将数据用于标注任务和训练模型等与数据提供方约定的目的，不得将数据用于其他商业用途或传播给未经授权的人员。

                标注结果归属：标注结果的知识产权归属于数据提供方，数据标注平台不得将标注结果用于其他用途，也不得将标注结果提供给未经授权的人员。

                数据安全：数据标注平台应采取合理的安全措施，保护数据的安全性和完整性，防止数据被非法获取、篡改或丢失。

                数据质量：数据标注平台应确保标注人员按照约定的标准进行标注，提供高质量的标注结果。

                数据备份：数据标注平台应定期对数据进行备份，以防止数据丢失或损坏。

                合作终止：当双方合作结束时，数据标注平台应将所有数据和相关信息交还给数据提供方，并删除或销毁与数据提供方相关的数据副本。

                违约责任：如果数据标注平台违反协议约定，导致数据提供方遭受损失，数据标注平台应承担相应的法律责任。

                法律适用和争议解决：本协议适用于中华人民共和国的法律，并在发生争议时，双方应通过友好协商解决。如协商不成，应提交有管辖权的人民法院解决。

                以上为数据标注平台的数据协议，双方应严格遵守并履行协议中的各项约定。
            </div>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="centerDialogVisible = false">确 定</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
export default {
    name: "PermissionRequest",
    components: {

    },
    data() {
        let validatecompany = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('请填写公司名称'));
            } else {
                callback()
            }
        };
        let validateposition = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请填写个人职位'));
            } else {
                callback()
            }
        };
        let validatereason = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请填写申请原因'));
            } else {
                callback()
            }
        };
        let validateevidence = (rule, value, callback) => {
            if (value.length === 0) {
                return callback(new Error('请上传申请证明材料'));
            } else {
                callback()
            }
        };
        let validateagree = (rule, value, callback) => {
            if (!value) {
                return callback(new Error('请勾选平台项目协议'));
            } else {
                callback()
            }
        };
        return {
            centerDialogVisible: false,
            agreedisabled: true,
            req: {
                company: "",
                position: "",
                reason: "",
                evidence: [],
                agree: false
            },
            reqrule: {
                company: [
                    { required: true, validator: validatecompany, trigger: 'blur' }
                ],
                position: [
                    { required: true, validator: validateposition, trigger: 'blur' }
                ],
                reason: [
                    { required: true, validator: validatereason, trigger: 'blur' }
                ],
                evidence: [
                    { required: true, validator: validateevidence, trigger: 'blur' }
                ],
                agree: [
                    { required: true, validator: validateagree, trigger: 'blur' }
                ]
            }
        }
    },
    computed: {

    },
    methods: {
        submit() {
            this.$refs.form.validate(result => {
                if (result) {
                    console.log(this.req);
                    this.$message.success("申请成功")
                }
            })  
        },
        uploadchange(file) {
            console.log(file);
            if (file.raw.size / 1024 / 1024 > 20) {
                this.$message({ type: "warning", message: file.name + "大小超过20MB" })
                this.$refs.upload.onRemove(file)
                return
            } else if (file.name.split(".")[file.name.split(".").length - 1] !== "pdf") {
                console.log();
                this.$message({ type: "warning", message: file.name + "文件格式不正确，请上传pdf文件" })
                this.$refs.upload.onRemove(file)
                return
            }
            this.req.evidence.push(file)
        },
        uploadremove(file) {
            console.log(file);
            this.req.evidence = this.req.evidence.filter(item => {
                return item.name !== file.name
            })
        },
    },
    mounted() {
        let a
         console.log(a);
    },
}
</script>
<style scoped>
.form {
    font-size: 30px;
    padding: 15px;
    height: 460px;
    overflow-y: auto;
}

.formitem {
    width: 60%;
    text-align: left;

}

.box-card {
    width: 95%;
    height: 598px;
    margin-left: 1%;
}

.cardheader {
    display: flex;
    justify-content: left;
    padding-left: 15px;
    align-items: center;
    font-size: 25px;
}</style>