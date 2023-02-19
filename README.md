# ZMBOX-Remastered

## 原理是通过网页API返回的Json数据,进行解析获取数据

## API
1. QQ音乐
   * 无需申请可直接使用
        > **搜索:** `https://c.y.qq.com/splcloud/fcgi-bin/smartbox_new.fcg?_=/*QQ账号*/&format=json&key=/*搜索内容*/&limit=/*返回数量*/`
   * 需要申请
        > **官方API:** `https://developer.y.qq.com`
2. 网易云音乐
   * 无需申请可直接使用
        > **搜索:** `https://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=/*搜索内容*/&type=1&offset=0&total=true&limit=/*返回数量*/`

        > **歌曲(无图片):** `http://music.163.com/api/song/enhance/player/url?id=/*歌曲ID*/&ids=[/*歌曲ID*/]&br=3200000`

        > **歌词:** `http://music.163.com/api/song/media?id=/*歌曲ID*/`

        > **获取歌曲详情(无歌词):** `https://tenapi.cn/wyyinfo/?id=/*歌曲ID*/`

        > **其他开发者写的API(需要部署)** `https://neteasecloudmusicapi.js.org/#/`
   * 需要申请
        > **官方API:** `https://developer.music.163.com/st/developer/`
3. 酷狗音乐
    * 无需申请可直接使用
        > **搜索:** `http://mobilecdn.kugou.com/api/v3/search/song?keyword=/*搜索内容*/&page=1&pagesize=/*返回数量*/`

        > **获取歌曲详细信息(需要设置请求头):** `https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=/*每首歌的hash*/&album_id=/*每首歌的album_id*/&album_audio_id=/*每首歌的album_audio_id*/`
4. Spotify
    
    **此API需要自己申请自己写JS**

    [可以参考我写的(很垃圾的JS代码)](https://zzhenjie.github.io/Spotify-API-Document/#/)

    * 需要申请
        > **官方API:** `https://developer.spotify.com`

[开发视频合集](https://space.bilibili.com/1362205077/channel/seriesdetail?sid=2973873&ctype=0)