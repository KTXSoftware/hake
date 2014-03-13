#include "ImageTool.h"
#include "Files.h"
#include "KhaExporter.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <algorithm>
#include <cmath>

using namespace kake;

namespace {
	typedef unsigned char u8;
	typedef unsigned int u32;

	int k_round(float value) {
		return (int)std::floor(value + 0.5f);
	}

	u32 sample(u32* image, int w, int h, float x, float y) {
		float posx = x * w;
		float posy = y * h;
		int xx = k_round(posx);
		int yy = k_round(posy);
		xx = std::min(std::max(0, xx), w - 1);
		yy = std::min(std::max(0, yy), h - 1);
		return image[yy * w + xx];
	}

	u32* scale(u32* image, int sw, int sh, int dw, int dh) {
		u32* data = new u32[dw * dh];
		for (int y = 0; y < dh; ++y) {
			for (int x = 0; x < dw; ++x) {
				data[y * dw + x] = sample(image, sw, sh, (float)x / (float)dw, (float)y / (float)dh);
			}
		}
		return data;
	}

	u8* removeColor(u8* image, int w, int h, int red, int green, int blue) {
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				if (
					image[y * w * 4 + x * 4 + 0] == red
					&& image[y * w * 4 + x * 4 + 1] == green
					&& image[y * w * 4 + x * 4 + 2] == blue
				) {
						image[y * w * 4 + x * 4 + 3] = 0;
				}
			}
		}
		return image;
	}
}

void hake::exportImage(Path from, Path to, Json::Value& asset, bool premultiplyAlpha) {
	premultiplyAlpha = false;
	if (!Files::exists(to.parent())) Files::createDirectories(to.parent());
	if (!premultiplyAlpha && (!asset.has("scale") || asset["scale"].number() == 1 || asset["scale"].number() == 0) && !asset.has("background")) KhaExporter::copyFile(from, to);
	else {
		int w;
		int h;
		int comp;
		u8* image = stbi_load(from.toString().c_str(), &w, &h, &comp, 4);
		if (image == nullptr) throw std::runtime_error("Could not read image.");

		if (premultiplyAlpha) {
			for (int y = 0; y < h; ++y) {
				for (int x = 0; x < w; ++x) {
					float alpha = image[y * w * 4 + h * 4 + 3] / 255.0f;
					image[y * w * 4 + h * 4 + 0] = k_round(image[y * w * 4 + h * 4 + 0] * alpha);
					image[y * w * 4 + h * 4 + 1] = k_round(image[y * w * 4 + h * 4 + 1] * alpha);
					image[y * w * 4 + h * 4 + 2] = k_round(image[y * w * 4 + h * 4 + 2] * alpha);
				}
			}
		}

		if (asset.has("scale") && asset["scale"].number() != 0 && asset["scale"].number() != 1) {
			image = (u8*)scale((u32*)image, w, h, w * asset["scale"].number(), h * asset["scale"].number());
			w *= asset["scale"].number();
			h *= asset["scale"].number();
		}

		//	BufferedImage outImage = new BufferedImage(image.getWidth(null), image.getHeight(null), BufferedImage.TYPE_4BYTE_ABGR);
		//	Graphics2D g2d = (Graphics2D)outImage.getGraphics();
		//	if (asset.circle) {
		//		RenderingHints hints = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		//		g2d.addRenderingHints(hints);
		//		g2d.setColor(new Color(1.0f, 1.0f, 1.0f, 0.0f));
		//		g2d.fillRect(0, 0, image.getWidth(null), image.getHeight(null));
		//		g2d.setColor(Color.BLACK);
		//		g2d.fillOval(0, 0, image.getWidth(null), image.getHeight(null));
		//		g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_ATOP));
		//	}
		//	g2d.drawImage(image, 0, 0, null);
		//	g2d.dispose();
		
		if (asset.has("background")) {
			int red = asset["background"]["red"].number();
			int green = asset["background"]["green"].number();
			int blue = asset["background"]["blue"].number();
			image = removeColor(image, w, h, red, green, blue);
		}

		stbi_write_png(to.toString().c_str(), w, h, 4, image, 0);
	}
}
