#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class ppmImage
{
public:
    ppmImage(const string source_ppm_file_name);//CREATES OBJECT FORM FILE
    ppmImage(int width,int height);//CREATES AN OBJECT ACCORDING TO THE GIVEN DIMENSIONS
    ppmImage(){}//DEFAULT CONSTRUCTOR

    struct RGB//STRUCT FOR 2D VECTOR(RED,GREEN,BLUE)
    {
      unsigned char R;
      unsigned char G;
      unsigned char B;
    };

    vector<vector<RGB> > Pixels;

    int GetWidth()const {return width;}
    int GetHeight()const{return height;}
    string GetP()const{return P;}
    int GetRGBSize()const{return RGBSize;}

    void SetWidth(int w) {width = w;}
    void SetHeight(int h){height = h;}
    void SetP(string p){P = p;}
    void SetRGBSize(int size){RGBSize = size;}


    void printDimension(){ cout << "Width: " << width << endl << "Height: " << height << endl;}
    void printPixelInformation(int w,int h){//DIDNT WORK I DON'T KNOW WHY
        cout << this->Pixels[h][w].R << " " << this->Pixels[h][w].G << " " << this->Pixels[h][w].B << endl;
    }
    void changePixelInformation(int w,int h);



private:

    int width,height;
    string P;
    int RGBSize;

};

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage& source, int color_choice);


int main(int argc, char** argv){

    int choice_number;
    char temp = argv[1][0];
    choice_number = temp - '0';
    string ppm_file_name = argv[2];
    int i=0;

    if(argc > 3) exit(0);

    ppmImage MyPPMObj;

    if(choice_number==1)
    {
        read_ppm(ppm_file_name,MyPPMObj);
        write_ppm("o1.ppm",MyPPMObj);
    }

    else if(choice_number==2)
    {
        read_ppm(ppm_file_name,MyPPMObj);
        if(swap_channels(MyPPMObj,1)!=1){
          cerr << "Couldn't Swap Try Again" << endl;
          exit(0);
        }
        write_ppm("o2.ppm",MyPPMObj);
    }

    else if(choice_number==3)
    {
        read_ppm(ppm_file_name,MyPPMObj);
        if(swap_channels(MyPPMObj,2)!=1){
          cerr << "Couldn't Swap Try Again" << endl;
          exit(0);
        }
        write_ppm("o3.ppm",MyPPMObj);
    }

    else if(choice_number==4)
    {
        read_ppm(ppm_file_name,MyPPMObj);
        if(swap_channels(MyPPMObj,3)!=1){
          cerr << "Couldn't Swap Try Again" << endl;
          exit(0);
        }
        write_ppm("o4.ppm",MyPPMObj);
    }

    else if(choice_number==5)
    {
        ppmImage newObj;
        read_ppm(ppm_file_name,MyPPMObj);
        newObj = single_color(MyPPMObj,1);
        write_ppm("o5.ppm",newObj);

    }

    else if(choice_number==6)
    {
        ppmImage newObj;
        read_ppm(ppm_file_name,MyPPMObj);
        newObj = single_color(MyPPMObj,2);
        write_ppm("o6.ppm",newObj);

    }

    else if(choice_number==7)
    {
        ppmImage newObj;
        read_ppm(ppm_file_name,MyPPMObj);
        newObj = single_color(MyPPMObj,3);
        write_ppm("o7.ppm",newObj);

    }

    else {
      cerr << "Choice number is not correct!" << endl;
      exit(0);
    }


}

ppmImage::ppmImage(const string source_ppm_file_name){

    ppmImage MyObj;
    read_ppm(source_ppm_file_name,MyObj);

}

ppmImage::ppmImage(int width,int height){

    if(width < 0 || height < 0) {
      cerr << "invalid dimension";
      exit(0);
    }

    for(int i=0 ; i < height ; i++)
      for(int j=0 ; j < width ; j++){
          Pixels[i][j].R = 255;
          Pixels[i][j].G = 255;
          Pixels[i][j].B = 255;
        }
}

void ppmImage::changePixelInformation(int w,int h){

    cout << "Enter to Change R:" << endl;
    cin >> this->Pixels[h][w].R;
    cout << endl;
    cout << "Enter to Change G:" << endl;
    cin >> this->Pixels[h][w].G;
    cout << endl;
    cout << "Enter to Change B:" << endl;
    cin >> this->Pixels[h][w].B;
    cout << endl;
}





int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){

    ifstream File(source_ppm_file_name);
    string TakeP;
    int rgbsize;
    int width,height;


    if(File.is_open())
    {
        File >> TakeP;
        if(TakeP != "P3") exit(0);
        File >> width >> height;
        File >> rgbsize;
        if(rgbsize>255) rgbsize = 255;

        destination_object.Pixels.resize(height);
        for(int i=0; i < height ; i++)
            destination_object.Pixels[i].resize(width);

    destination_object.SetWidth(width);
    destination_object.SetHeight(height);
    destination_object.SetP(TakeP);
    destination_object.SetRGBSize(rgbsize);


        int temp;
        for(int i=0 ; i < height ; i++)
            for(int j=0 ; j < width ; j++){
                File >> temp;
                destination_object.Pixels[i][j].R = temp;

                File >> temp;
                destination_object.Pixels[i][j].G = temp;

                File >> temp;
                destination_object.Pixels[i][j].B = temp;
            }
    return 1;
    }

    else
    {
      cerr << "Cannot open ppm file" << endl;
      return 0;
    }
File.close();
}

int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){

    ofstream File(destination_ppm_file_name);

    if(File.is_open())
    {
        File << source_object.GetP() << endl;
        File << source_object.GetWidth() << " " << source_object.GetHeight() << endl;
        File << source_object.GetRGBSize() << endl;

        for(int i=0 ; i < source_object.GetHeight() ; i++){
            for(int j=0 ; j < source_object.GetWidth() ; j++){

                File << (int)source_object.Pixels[i][j].R << " ";
                File << (int)source_object.Pixels[i][j].G << " ";
                File << (int)source_object.Pixels[i][j].B << " ";
          }
          File << "\n";
        }
      return 1;
    }

    else
    {
      cerr << "Cannot open ppm file" << endl;
      return 0;
    }

File.close();
}

int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){

int w = image_object_to_be_modified.GetWidth();
int h = image_object_to_be_modified.GetHeight();
int temp;

      if(swap_choice==1)  //SWAP RED AND GREEN
      {
        for(int i=0 ; i < h ; i++)
            for(int j=0 ; j < w ; j++){
                temp = image_object_to_be_modified.Pixels[i][j].R;
                image_object_to_be_modified.Pixels[i][j].R =  image_object_to_be_modified.Pixels[i][j].G;
                image_object_to_be_modified.Pixels[i][j].G = temp;
            }
      return 1;
      }

      else if(swap_choice==2)//SWAPS RED AND BLUE
      {
        for(int i=0 ; i < h ; i++)
            for(int j=0 ; j < w ; j++){
                temp = image_object_to_be_modified.Pixels[i][j].R;
                image_object_to_be_modified.Pixels[i][j].R =  image_object_to_be_modified.Pixels[i][j].B;
                image_object_to_be_modified.Pixels[i][j].B = temp;
            }
      return 1;
      }

      else if(swap_choice==3)//SWAP GREEN AND BLUE
      {
        for(int i=0 ; i < h ; i++)
            for(int j=0 ; j < w ; j++){
                temp = image_object_to_be_modified.Pixels[i][j].G;
                image_object_to_be_modified.Pixels[i][j].G =  image_object_to_be_modified.Pixels[i][j]  .B;
                image_object_to_be_modified.Pixels[i][j].B = temp;
            }
      return 1;
      }

      else return 1;


return 0;
}

ppmImage single_color(const ppmImage& source, int color_choice){

    ppmImage copyImage;
    int w = source.GetWidth();
    int h = source.GetHeight();

    copyImage = source;

    if(color_choice==1)
    {
      for(int i=0 ; i < h ; i++)
          for(int j=0 ; j < w ; j++){
              copyImage.Pixels[i][j].G = 0;
              copyImage.Pixels[i][j].B = 0;
          }
    }

    if(color_choice==2)
    {
     for(int i=0 ; i < h ; i++){
          for(int j=0 ; j < w ; j++){
              copyImage.Pixels[i][j].R = 0;
              copyImage.Pixels[i][j].B = 0;

          }

        }
    }

    if(color_choice==3)
    {
      for(int i=0 ; i < h ; i++)
          for(int j=0 ; j < w ; j++){
              copyImage.Pixels[i][j].R = 0;
              copyImage.Pixels[i][j].G = 0;
          }
    }

return copyImage;

}
