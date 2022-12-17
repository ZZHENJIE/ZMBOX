# ZMBOX
![](/Resource/Logo.ico)
## API
``` json
{
    "音乐平台":
    [
        {
            "Platform":"网易云音乐",
            "无需部署API":
            {
                "获取搜索内容":"https://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=/*搜索内容*/&type=1&offset=0&total=true&limit=10",
                "歌曲":"http://music.163.com/api/song/enhance/player/url?id=/*歌曲ID*/&ids=[/*歌曲ID*/]&br=3200000",
                "歌词":"http://music.163.com/api/song/media?id=/*歌曲ID*/",
                "获取歌曲详情":"https://tenapi.cn/wyyinfo/?id=/*歌曲ID*/"
            },
            "需部署API":
            {
                "API网站":"https://neteasecloudmusicapi.js.org/#/"
            }
        },

        {
            "Platform":"QQ音乐",
            "无需部署API":
            {
                "获取搜索内容":"https://c.y.qq.com/splcloud/fcgi-bin/smartbox_new.fcg?_=/*QQ账号*/&format=json&key=/*搜索内容*/&limit=10"
            },
            "需部署API":
            {
                "API网站":"https://rain120.github.io/qq-music-api/#/"
            }
        },

        {
            "Platform":"酷狗音乐",
            "无需部署API":
            {
                "获取搜索内容":"http://mobilecdn.kugou.com/api/v3/search/song?keyword=/*搜索内容*/&page=1&pagesize=10",
                "获取歌曲详细信息":"https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=/*每首歌的hash*/&album_id=/*每首歌的album_id*/&album_audio_id=/*每首歌的album_audio_id*/"
            }
        }
    ],

    "获取QQ信息":"https://api.leafone.cn/api/qq?qq=/*QQ号*/"
}
```
* 使用QT6.2LTS版本

* ***编译前先修改 server.h 内的服务器IP和端口号宏(改成自己服务器的)***

* 部署API推荐使用[Vercel](https://vercel.com/)

* [B站](https://space.bilibili.com/1362205077?spm_id_from=333.1007.0.0)

* [学习屋](https://zzhenjie.github.io/Learning_House/#/)