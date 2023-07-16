// Copyright (c) Ko Umetani. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef FACES_KEIFACE_H_
#define FACES_KEIFACE_H_

#include <M5Unified.h> // TODO(meganetaaan): include only the Sprite function not a whole library
#include <Avatar.h>

namespace m5avatar
{

  /**
   * 目のクラス
  */
  class KeiEye : public Drawable
  {

  private:
    uint16_t r;
    bool isLeft;

  public:
    KeiEye(uint16_t r, bool isLeft)
        : r{r}, isLeft{isLeft} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      Expression exp = ctx->getExpression();
      uint32_t x = rect.getCenterX();
      uint32_t y = rect.getCenterY();
      Gaze g = ctx->getGaze();
      float openRatio = ctx->getEyeOpenRatio();
      uint32_t offsetX = g.getHorizontal() * 3;
      uint32_t offsetY = g.getVertical() * 3;
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);

      if (openRatio > 0)
      {
        // Happy, Angry, Sad, Doubt, Sleepy, Neutral
        if (exp == Expression::Happy || exp == Expression::Sad)
        {
          // spi->fillCircle(x + offsetX, y + offsetY, r, primaryColor);
          int inner12 = 10;
          int inner3 = 15;
          if (!isLeft)
          {
            int rx = x + 10;
            spi->fillTriangle(rx-r+offsetX, y-r+offsetY, rx-r+offsetX, y+r+offsetY, rx+r+offsetX, y+offsetY, primaryColor);
            spi->fillTriangle(rx-r+offsetX, y-r+offsetY+inner12, rx-r+offsetX, y+r+offsetY-inner12, rx+r+offsetX-inner3, y+offsetY, backgroundColor);
          }
          else
          {
            int lx = x - 10;
            spi->fillTriangle(lx+r+offsetX, y-r+offsetY, lx+r+offsetX, y+r+offsetY, lx-r+offsetX, y+offsetY, primaryColor);
            spi->fillTriangle(lx+r+offsetX, y-r+offsetY+inner12, lx+r+offsetX, y+r+offsetY-inner12, lx-r+offsetX+inner3, y+offsetY, backgroundColor);
          }
        }
        else if (exp == Expression::Angry)
        {
          uint16_t keiEyeColor = 0;
          keiEyeColor = M5.Lcd.color565(196,64,178);

          int by = y - 15;
          int ey = y - 3;
          int offset_eye = 5;
          if (!isLeft)
          {
            int rx = x + offset_eye;
            int erx = rx + 5;
            // まつ毛
            spi->fillTriangle(rx-15, by-25, rx-5, by-7, rx+10, by-10, TFT_BLACK);
            spi->fillEllipse(rx , by, 40, 15, TFT_BLACK);
            spi->fillEllipse(rx , by+10, 50, 14, backgroundColor);
            spi->fillEllipse(rx-38 , by, 8, 13, TFT_BLACK);
            spi->fillTriangle(rx-48, by-25, rx-48, by+15, rx-28, by+15, backgroundColor);
            // 瞳
            spi->fillEllipse(erx-1, ey, 18, 23, keiEyeColor);
            spi->fillEllipse(erx, ey, 13, 20, primaryColor);
            spi->fillEllipse(erx, ey, 11, 17, keiEyeColor);
            spi->fillEllipse(erx, ey, 8, 13, primaryColor);
            spi->fillEllipse(erx, ey, 6, 11, keiEyeColor);
            spi->fillEllipse(erx, ey, 4, 6, primaryColor);
            // 上まつ毛の被せ
            spi->fillArc(rx, by+55, 62, 70, 250, 290, TFT_BLACK);
            // 下まつ毛のスライス
            spi->fillRect(rx-15, by+32, 30, 10, backgroundColor);
          }
          else
          {
            int lx = x - offset_eye;
            int elx = lx - 5;
            // まつ毛
            spi->fillTriangle(lx+15, by-25, lx+5, by-7, lx-10, by-10, TFT_BLACK);
            spi->fillEllipse(lx , by, 40, 15, TFT_BLACK);
            spi->fillEllipse(lx , by+10, 50, 14, backgroundColor);
            spi->fillEllipse(lx+38 , by, 8, 13, TFT_BLACK);
            spi->fillTriangle(lx+48, by-25, lx+48, by+15, lx+28, by+15, backgroundColor);
            // 瞳
            spi->fillEllipse(elx+1, ey, 18, 23, keiEyeColor);
            spi->fillEllipse(elx, ey, 13, 20, primaryColor);
            spi->fillEllipse(elx, ey, 11, 17, keiEyeColor);
            spi->fillEllipse(elx, ey, 8, 13, primaryColor);
            spi->fillEllipse(elx, ey, 6, 11, keiEyeColor);
            spi->fillEllipse(elx, ey, 4, 6, primaryColor);
            // 上まつ毛の被せ
            spi->fillArc(lx, by+55, 62, 70, 250, 290, TFT_BLACK);
            // 下まつ毛のスライス
            spi->fillRect(lx-15, by+32, 30, 10, backgroundColor);
          }
        }
        else if (exp == Expression::Doubt)
        {
          spi->fillRect(x-5, y-13, 10, 10, primaryColor);
          spi->fillRect(x-5, y+3+1, 10, 10, primaryColor);
          spi->fillRect(x-5, y+3+10+1, 10, 8, primaryColor);
          spi->fillRect(x-5, y+3+10+1, 4, 4, backgroundColor);
          spi->fillRect(x-5, y+3+10+1, 2, 6, backgroundColor);
          spi->fillTriangle(x, y+3+10+6+2, x+5, y+3+10+6+2, x+5, y+3+10+3 ,backgroundColor);
        }
        else if (exp == Expression::Sleepy)
        {
          spi->fillRect(x-30, y-5, 60, 7, primaryColor);
        }
        else if (exp == Expression::Neutral)
        {
          spi->fillCircle(x + offsetX, y + offsetY, r, primaryColor);
        }
      }
      else
      {
        int x1 = x - r + offsetX;
        int y1 = y - 2 + offsetY;
        int w = r * 2;
        int h = 4;
        spi->fillRect(x1, y1, w, h, primaryColor);
      }

    }
  };

  /**
   * 口のクラス
  */
  class KeiMouth : public Drawable
  {
  private:
    uint16_t minWidth;
    uint16_t maxWidth;
    uint16_t minHeight;
    uint16_t maxHeight;

  public:
    KeiMouth() : KeiMouth(0, 0, 0, 0) {}
    KeiMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
            uint16_t maxHeight)
        : minWidth{minWidth},
          maxWidth{maxWidth},
          minHeight{minHeight},
          maxHeight{maxHeight} {}

    void draw(M5Canvas *spi, BoundingRect rect, DrawContext *ctx)
    {
      ColorPalette *cp = ctx->getColorPalette();
      uint16_t primaryColor = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
      uint16_t backgroundColor = ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);
      float breath = _min(1.0f, ctx->getBreath());
      float openRatio = ctx->getMouthOpenRatio();
      int h = minHeight + (maxHeight - minHeight) * openRatio;
      int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
      int x = rect.getLeft() - w / 2;
      int y = rect.getTop() - h / 2 + breath * 2;
      Expression exp = ctx->getExpression();

      uint16_t doubtMouthColor = 0;
      doubtMouthColor = M5.Lcd.color565(255,218,227);

      if (exp != Expression::Sad)
      {
        spi->fillRect(x, y, w, h, primaryColor);
      }
      else
      {
          int dy = y -20;
          spi->fillRoundRect(x, dy, w, 40, 20, doubtMouthColor);
          spi->fillRoundRect(x, dy+10, w, 30, 10, doubtMouthColor);
          int ex = x + w/2;
          int ey = dy;
          spi->fillEllipse(ex, ey-2, 20, 3, backgroundColor);
          spi->fillEllipse(ex, ey+42, 30, 3, backgroundColor);
      }
    }
  };


  /**
   * Faceクラスを継承したKei顔描画用のクラス
  */
  class KeiFace : public Face
  {
  public:
    KeiFace()
        : Face(new KeiMouth(50, 70, 11, 50), new BoundingRect(183, 160),
               new KeiEye(30, false), new BoundingRect(118, 54),
               new KeiEye(30, true), new BoundingRect(118, 266),
               new Eyeblow(12, 0, false), new BoundingRect(71, 50),
               new Eyeblow(12, 0, true), new BoundingRect(73, 270)) {}
  };

} // namespace m5avatar

#endif // FACES_KEIFACE_H_
