// image_crop.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include <boost/gil/extension/io/bmp.hpp>

using namespace std;

void cropImageCenter(const std::string & source,
					 const std::string & result,
					 int result_w, int result_h)
{
    using namespace boost::gil;

    any_image<rgb8_image_t> source_image;
    read_image(source, source_image, bmp_tag());
    
    // Формируем представление выреза в источнике
    int crop_left = (source_image.width() - result_w) / 2;
    int crop_top = (source_image.height() - result_h) / 2;
    int crop_width = result_w;
    int crop_height = result_h;
    if (crop_left < 0) crop_left = 0;
    if (crop_top < 0) crop_top = 0;
    if (crop_width > source_image.width()) crop_width = source_image.width();
    if (crop_height > source_image.height()) crop_height = source_image.height();
    auto crop_view = subimage_view(view(source_image), crop_left, crop_top, crop_width, crop_height); // вырез

    // Белые поля при необходимости
    if (crop_width < result_w || crop_height < result_h)
    {   // придется использовать новый буфер, чтобы сделать поля
        any_image<rgb8_image_t> bufer;
        bufer.recreate(result_w, result_h);
        fill_pixels(view(bufer), rgb8_pixel_t(255,255,255));
        int margin_left = (result_w - crop_width) / 2;
        int margin_top = (result_h - crop_height) / 2;
        copy_pixels(crop_view, subimage_view(view(bufer), margin_left, margin_top, crop_width, crop_height));
        write_view(result, view(bufer), bmp_tag());
    }
    else
	{   // сохраняем представление выреза
		write_view(result, crop_view, bmp_tag()); 
	}
}

const int ERROR_CODE = 1;
const int CROP_WIDTH = 512;
const int CROP_HEIGHT = 512;

void usage()
{
    cout << "usage: image_crop <source> <dest>" << endl
         << "crop center " << CROP_WIDTH <<"x"<< CROP_HEIGHT << " rectangle from source and save it to dest" << endl;
}

int main(int argc, char * argv[])
{
	try
	{
        if (argc < 3)
        {
            usage();
            return ERROR_CODE;
        }
		cropImageCenter(argv[1], argv[2], CROP_WIDTH, CROP_HEIGHT);
        return 0;
	}
	catch (ios_base::failure & e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "unhandled exception" << endl;
    }
    usage();

    return ERROR_CODE;
}
