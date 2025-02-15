typedef array<int> ImageData;

// Serialize images and send them across the internet! 1980 all over again
class ImageLoader: Managed
{
	private void ImageLoader();
	private void ~ImageLoader();

    static const int MAX_IMAGE_SIZE = 4096 * 32;
    
    static ImageData LoadImage(string path)
    {
        ImageData image_data();
        
        if (!FileExist(path)) {
            Error("Image not found! " + path);
            return image_data;
        }
        
        FileSerializer image_serializer();
        if (!image_serializer.Open(path)) {
            Error("Failed to open Image Serializer");
            image_serializer.Close();
            return image_data;
        }
        
        for (int i = 0; i < MAX_IMAGE_SIZE; i++) {
            int byte;
            image_serializer.Read(byte);
            image_data.Insert(byte);
        }
        
        image_serializer.Close();
        
        // Clean up the zeros at the end
        for (int j = image_data.Count() - 1; j >= 0; j--) {
            if (image_data[j] != 0) {
                return image_data;
            }
            
            image_data.Remove(j);
        }
        
        return image_data;
    }
    
    static bool SaveImage(ImageData image_data, string path)
    {
        FileSerializer image_serializer();
        if (FileExist(path)) {
            if (!DeleteFile(path)) {
                Error("Failed to delete file " + path);
                return false;
            }
        }
        
        if (!image_serializer.Open(path, FileMode.WRITE)) {
            Error("Failed to open Image Serializer");
            image_serializer.Close();
            return false;
        }
        
        image_serializer.Close();
        
        if (!image_serializer.Open(path, FileMode.APPEND)) {
            Error("Failed to open Image Serializer");
            image_serializer.Close();
            return false;
        }
        
        foreach (int byte: image_data) {
            image_serializer.Write(byte);
        }
        
        image_serializer.Close();
        return FileExist(path);
    }
}