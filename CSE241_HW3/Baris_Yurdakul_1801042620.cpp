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
    void changePixelInformation(int w,int h);

    friend ppmImage operator +(const ppmImage& obj1 , const ppmImage& obj2);
    friend ppmImage operator -(const ppmImage& obj1 , const ppmImage& obj2);
    friend ostream& operator <<(ostream &out ,const ppmImage obj);
    int& operator()(int rowValue ,int columnValue ,int colorChannel);

private:

    int width,height;
    string P;
    int RGBSize;

};

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage& source, int color_choice);
bool checkSizeEq(const ppmImage obj1,const ppmImage obj2);

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filename_image1);

int main(int argc, char** argv){

    int choice_number;
    char temp = argv[1][0];
    choice_number = temp - '0';
    string ppm_file_name1 = argv[2];
    string ppm_file_name2,ppm_file_name3;
    if(argv[3] != NULL) ppm_file_name2 = argv[3];
    if(argv[4] != NULL) ppm_file_name3 = argv[4];
    int i=0;

    if(argc > 5) exit(0);

    ppmImage MyPPMObj;

    if(choice_number==1)
    {
        read_ppm(ppm_file_name1,MyPPMObj);
        write_ppm(ppm_file_name2  ,MyPPMObj);
        if(ppm_file_name2 == "\0" || ppm_file_name3 == "\0") exit(0);
        else test_addition(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    }

    else if(choice_number==2)
    {
        read_ppm(ppm_file_name1,MyPPMObj);
        if(swap_channels(MyPPMObj,1)!=1){
        cerr << "Couldn't Swap Try Again" << endl;
        exit(0);
        }
        write_ppm(ppm_file_name2,MyPPMObj);


        if(ppm_file_name2 == "\0" || ppm_file_name3 == "\0") exit(0);
        else test_subtraction(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    }

    else if(choice_number==3)
    {
        read_ppm(ppm_file_name1,MyPPMObj);
        if(swap_channels(MyPPMObj,2)!=1){
          cerr << "Couldn't Swap Try Again" << endl;
          exit(0);
        }
        write_ppm(ppm_file_name2,MyPPMObj);
    }

    else if(choice_number==4)
    {
        read_ppm(ppm_file_name1,MyPPMObj);
        if(swap_channels(MyPPMObj,3)!=1){
          cerr << "Couldn't Swap Try Again" << endl;
          exit(0);
        }
        write_ppm(ppm_file_name2,MyPPMObj);
    }

    else if(choice_number==5)
    {
        ppmImage newObj;
        read_ppm(ppm_file_name1,MyPPMObj);
        newObj = single_color(MyPPMObj,1);
        write_ppm(ppm_file_name2,newObj);

    }

    else if(choice_number==6)
    {
        ppmImage newObj;
        read_ppm(ppm_file_name1,MyPPMObj);
        newObj = single_color(MyPPMObj,2);
        write_ppm(ppm_file_name2,newObj);

    }

    else if(choice_number==7)
    {
        ppmImage newObj;
        read_ppm(ppm_file_name1,MyPPMObj);
        newObj = single_color(MyPPMObj,3);
        write_ppm(ppm_file_name2,newObj);

    }

    else {
      cerr << "Choice number is not correct!" << endl;
      exit(0);
    }


}

ppmImage operator +(const ppmImage& obj1 , const ppmImage& obj2){

    int w,h,w1,h1,w2,h2,w3,h3;
    ppmImage emptyImage;
    ppmImage newImage;
    int MaxValue = obj1.GetRGBSize();

    if(checkSizeEq(obj1,obj2) == 0){//MAKING EMPTY

        w1 = obj1.GetWidth();
        h1 = obj1.GetHeight();

        w2 = obj2.GetWidth();
        h2 = obj2.GetHeight();

        w3 = obj1.GetWidth();
        h3 = obj1.GetHeight();

        cerr << "Object sizes are not equal!!" << endl;

        for(int i=0 ; i < h3 ; i++)
            for(int j=0 ; j < w3 ; j++){
                emptyImage.Pixels[i][j].R = 0;
                emptyImage.Pixels[i][j].G = 0;
                emptyImage.Pixels[i][j].B = 0;
            }
      return emptyImage;
      }

      if(checkSizeEq(obj1,obj2) == 1){//ADDS TWO OBJECTS

        w = obj1.GetWidth();
        h = obj1.GetHeight();

        for(int i=0 ; i < h3 ; i++)
            for(int j=0 ; j < w3 ; j++){
              newImage.Pixels[i][j].R = obj1.Pixels[i][j].R + obj2.Pixels[i][j].R;
              if(newImage.Pixels[i][j].R > MaxValue) newImage.Pixels[i][j].R = MaxValue;
              newImage.Pixels[i][j].G = obj1.Pixels[i][j].G + obj2.Pixels[i][j].G;
              if(newImage.Pixels[i][j].G > MaxValue) newImage.Pixels[i][j].G = MaxValue;
              newImage.Pixels[i][j].B = obj1.Pixels[i][j].B + obj2.Pixels[i][j].B;
              if(newImage.Pixels[i][j].B > MaxValue) newImage.Pixels[i][j].B = MaxValue;
        }//End of for
      return newImage;
      }//End of if
    }

ppmImage operator -(const ppmImage& obj1 , const ppmImage& obj2){

    int w,h,w1,h1,w2,h2,w3,h3;
    ppmImage emptyImage;
    ppmImage newImage;
    int MaxValue = obj1.GetRGBSize();

    if(checkSizeEq(obj1,obj2) == 0){//MAKING EMPTY

        w1 = obj1.GetWidth();
        h1 = obj1.GetHeight();

        w2 = obj2.GetWidth();
        h2 = obj2.GetHeight();

        w3 = obj1.GetWidth();
        h3 = obj1.GetHeight();

        cerr << "Object sizes are not equal!!" << endl;

        for(int i=0 ; i < h3 ; i++)
            for(int j=0 ; j < w3 ; j++){
                emptyImage.Pixels[i][j].R = 0;
                emptyImage.Pixels[i][j].G = 0;
                emptyImage.Pixels[i][j].B = 0;
            }
      return emptyImage;
      }

      if(checkSizeEq(obj1,obj2) == 1){//SUBTRACTS TWO OBJECTS

        w = obj1.GetWidth();
        h = obj1.GetHeight();

        for(int i=0 ; i < h3 ; i++)
            for(int j=0 ; j < w3 ; j++){
              newImage.Pixels[i][j].R = obj1.Pixels[i][j].R - obj2.Pixels[i][j].R;
              if(newImage.Pixels[i][j].R < 0) newImage.Pixels[i][j].R = 0;
              newImage.Pixels[i][j].G = obj1.Pixels[i][j].G - obj2.Pixels[i][j].G;
              if(newImage.Pixels[i][j].G < 0) newImage.Pixels[i][j].G = 0;
              newImage.Pixels[i][j].B = obj1.Pixels[i][j].B - obj2.Pixels[i][j].B;
              if(newImage.Pixels[i][j].B < 0) newImage.Pixels[i][j].B = 0;
        }//End of for
      return newImage;
      }//End of if
    }


ostream& operator <<(ostream &out ,const ppmImage obj){

      out << "P : " << obj.GetP() << endl;
      out << "Width : " << obj.GetWidth() << endl;
      out << "Height : " << obj.GetHeight() << endl;
      out << "Max Value : " << obj.GetRGBSize() << endl;

      for(int i=0 ; i < obj.GetHeight() ; i++){
          for(int j=0 ; j < obj.GetWidth() ; j++){
              out << obj.Pixels[i][j].R << " ";
              out << obj.Pixels[i][j].G << " ";
              out << obj.Pixels[i][j].B << " ";
          }
        out << endl;
      }
  return out;
}

int& ppmImage::operator()(int rowValue ,int columnValue ,int colorChannel){

    int& R = (int&)Pixels[columnValue][rowValue].R;
    int& G = (int&)Pixels[columnValue][rowValue].G;
    int& B = (int&)Pixels[columnValue][rowValue].B;

    if(rowValue < 0 || columnValue < 0) cerr << "Check your function call and try again" << endl;

    if(colorChannel == 1){
        return R;
    }
    if(colorChannel == 2){
        return G;
    }
    if(colorChannel == 3){
        return B;
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
                temp = image_object_to_be_modified(j,i,1);
                image_object_to_be_modified(j,i,1) = image_object_to_be_modified(j,i,2);
                image_object_to_be_modified(j,i,2) = temp;
            }
      return 1;
      }

      else if(swap_choice==2)//SWAPS RED AND BLUE
      {
        for(int i=0 ; i < h ; i++)
            for(int j=0 ; j < w ; j++){
                temp = image_object_to_be_modified(j,i,1);
                image_object_to_be_modified(j,i,1) = image_object_to_be_modified(j,i,3);
                image_object_to_be_modified(j,i,3) = temp;
            }
      return 1;
      }

      else if(swap_choice==3)//SWAP GREEN AND BLUE
      {
        for(int i=0 ; i < h ; i++)
            for(int j=0 ; j < w ; j++){
              temp = image_object_to_be_modified(j,i,2);
              image_object_to_be_modified(j,i,2) = image_object_to_be_modified(j,i,3);
              image_object_to_be_modified(j,i,3) = temp;
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
              copyImage(j,i,2) = 0;
              copyImage(j,i,3) = 0;
          }
    }

    if(color_choice==2)
    {
     for(int i=0 ; i < h ; i++){
          for(int j=0 ; j < w ; j++){
              copyImage(j,i,1) = 0;
              copyImage(j,i,3) = 0;

          }

        }
    }

    if(color_choice==3)
    {
      for(int i=0 ; i < h ; i++)
          for(int j=0 ; j < w ; j++){
              copyImage(j,i,1) = 0;
              copyImage(j,i,2) = 0;
          }
    }

return copyImage;

}

bool checkSizeEq(const ppmImage obj1,const ppmImage obj2){

    int width1 = obj1.GetWidth();
    int height1 = obj1.GetHeight();

    int width2 = obj2.GetWidth();
    int height2 = obj2.GetHeight();

    if((width1 == width2) && (height1 == height2)) return 1;
    else return 0;

}


int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){

    ppmImage TestObj1,TestObj2,Obj3;

    read_ppm(filename_image1,TestObj1);
    read_ppm(filename_image2,TestObj2);

    Obj3 = TestObj1 + TestObj2;

    write_ppm(filename_image3,Obj3);

  return 1;
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){

    ppmImage TestObj1,TestObj2,Obj3;

    read_ppm(filename_image1,TestObj1);
    read_ppm(filename_image2,TestObj2);

    Obj3 = TestObj1 - TestObj2;

    write_ppm(filename_image3,Obj3);

  return 1;
}

int test_print(const string filename_image1){

    ppmImage PrintObj;

    read_ppm(filename_image1,PrintObj);

    cout << PrintObj;

  return 1;
}
