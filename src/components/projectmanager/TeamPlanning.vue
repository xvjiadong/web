<template>
    <div>
        <el-card class="friendlist">
            <div slot="header" style="padding:0;text-align:left">
                <span style="font-size:20px;font-weight:600;color:#606266">好友列表</span>
            </div>

        </el-card>
    </div>
</template>

<script>
export default {

}
</script>

<style scoped>
.friendlist {
    width: 20%;
    height: 690px;
    overflow-y: auto;
}

/deep/.el-card__header {
    padding: 15px;
    border-bottom: 1px solid #EBEEF5;
    box-sizing: border-box;
}
</style>