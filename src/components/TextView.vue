<template>
    <div>
        <span id="s">一二三<span>四</span>五,上山打老虎</span>
    </div>
</template>

<script>
export default {
    data() {
        return {
            str: ""
        }
    },
    methods: {

    },
    mounted() {
        let s = document.getElementById("s")
        s.addEventListener("mouseup", () => {
            let selection=window.getSelection()
            let range = selection.getRangeAt(0)
            if (range.collapsed) {
                return
            }
            let str = s.innerHTML
            s.innerHTML=""
            let l = str.substring(0, selection.anchorOffset)
            console.log(selection);
            let sl = document.createElement('span')
            sl.innerHTML = l
            s.appendChild(sl)
            for (let i = range.startOffset; i <selection.focusOffset; i++){
                let span = document.createElement('span')
                span.innerHTML = str[i]
                s.appendChild(span)
            }
            let r = str.substring(selection.focusOffset)
            let sr = document.createElement('span')
            sr.innerHTML = r
            s.appendChild(sr)
             
        })
    },
}
</script>