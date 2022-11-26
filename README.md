# ZMBOX

> 可以下载一些网易云音乐需要VIP才能下载的歌曲

## 项目用到的API
``` json
[
    {
        "Name":"网易云音乐",
        "获取搜索内容":"http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=/*搜索内容*/&type=1&offset=0&total=true&limit=10"
        "歌曲":"http://music.163.com/api/song/enhance/player/url?id=/*歌曲ID*/&ids=[/*歌曲ID*/]&br=3200000",
        "歌词":"http://music.163.com/api/song/media?id=/*歌曲ID*/",
    }

    {
        "Name":"QQ音乐",
        "获取搜索内容":"https://c.y.qq.com/splcloud/fcgi-bin/smartbox_new.fcg?_=/*QQ账号*/&format=json&key=/*搜索内容*/&limit=10"
    }

    {
        "Name":"酷狗音乐",
        "获取搜索内容":"http://mobilecdn.kugou.com/api/v3/search/song?keyword=/*搜索内容*/&page=1&pagesize=10",
        "获取歌曲详细信息":"https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=/*每首歌的hash*/&album_id=/*每首歌的album_id*/&album_audio_id=/*每首歌的album_audio_id*/"
    }

    {
        "Name":"Other",
        "获取QQ信息":"https://api.leafone.cn/api/qq?qq=/*QQ号*/"
    }
]
```

> 作者B站:https://space.bilibili.com/1362205077?spm_id_from=333.1007.0.0

> 作者学习屋项目:https://zzhenjie.github.io/Learning_House/#/



https://dl.stream.qqmusic.qq.com/C400
003E5Ddz3b429u
.m4a?
guid=4925389888
&vkey=2861D26F470CD64B00E51EBE838F4692590FDC04EFD5FCFD72F4A085D9A4904CC9A73100D15AD261CC961EBCA310DD1A87AD66565EE2C23B
&uin=508916879
&fromtag=120032