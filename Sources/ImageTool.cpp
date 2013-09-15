#include "ImageTool.h"
#include "KhaExporter.h"

using namespace kake;

void hake::exportImage(Path from, Path to, Json::Value& asset) {
	//if (!to.toFile().getParentFile().exists()) to.toFile().getParentFile().mkdirs();
	if ((!asset.has("scale") || asset["scale"].number() == 1 || asset["scale"].number() == 0) && !asset.has("background")) KhaExporter::copyFile(from, to);
	else {
		//try {
		//	Image image = ImageIO.read(from.toFile());
		//	if (image == null) {
		//		throw new IOException("Could not read image " + from + ".");
		//	}
		//	if (asset.scale != 0) {
		//		image = image.getScaledInstance((int)(image.getWidth(null) * asset.scale), (int)(image.getHeight(null) * asset.scale), BufferedImage.SCALE_FAST);
		//	}
		//		
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
		//		
		//	if (asset.background != null) {
		//		Color c = new Color(asset.background.red, asset.background.green, asset.background.blue);
		//		for (int y = 0; y < image.getHeight(null); ++y) {
		//			for (int x = 0; x < image.getWidth(null); ++x) {
		//				Color c2 = new Color(outImage.getRGB(x, y));
		//				if (c.getRed() == c2.getRed() && c.getGreen() == c2.getGreen() && c.getBlue() == c2.getBlue()) {
		//					outImage.setRGB(x, y, 0);
		//				}
		//			}
		//		}
		//	}
		//		
		//	ImageIO.write(outImage, "png", to.toFile());
		//}
		//catch (Exception ex) {
		//	Log.the().log(ex);
		//}
	}
}