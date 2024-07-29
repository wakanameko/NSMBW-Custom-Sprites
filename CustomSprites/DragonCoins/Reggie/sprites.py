class SpriteImage_DragonCoins(SLib.SpriteImage_StaticMultiple):  # 489
    @staticmethod
    def loadImages():
        if 'smwDragoncoin0' in ImageCache: return
        for i in range(1):
            ImageCache[f'smwDragoncoin{i}'] = SLib.GetImg(f'smwDragoncoin_{i}.png')

    def dataChanged(self):

        color = (self.parent.spritedata[2] & 0xF)

        self.image = ImageCache[f'smwDragoncoin{color}']
        self.offset = (0, -5)

        super().dataChanged()


ImageClasses = {
    489: SpriteImage_DragonCoins,  
}
