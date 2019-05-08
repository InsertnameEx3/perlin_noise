#include <iostream>
#include <fstream>
// Even though it is bad practice
using namespace std;

double Mersenne_Twister(int modulus, int multiplier, int increment, int seed){
    double variable = (seed * multiplier + increment) % modulus;
    return variable;
}




void Linear_Perlin(int *plane[], int height, int width, int detail, int *perlinPlane[]){
    
    
    //Take center 'depth' and cover it for the entire perlinPlane
    cout << plane[height/2][width/2];
    perlinPlane[height][width]; 
    perlinPlane = plane;
    
    //Steps:
    //1 add a new height every iteration for only the selected points
    //2 add this height linearly between points for each row
    //3 add this height linearly between points for each column

    

    //you subdive the grid every iteration
    // 3 points -> 5 -> 9 -> 16 -> 
    //detail = iteration/octave
    int subdivision = 3;    // we start at 3 points per row/column and subdivide every iteration/octave
    for(int i = 1; i < detail; ++i){    //We can skip the first iteration as that was in the perlinPlane initialization
        subdivision = ((subdivision-2) * 2) + 2;

        for(int widthSub = 0; widthSub < subdivision; ++widthSub){  //for each point in the subdivision
             for(int heightSub = 0; heightSub < subdivision; ++heightSub){  //for each point in the subdivision

            int pointHeight = height/subdivision*heightSub; 
            int pointWidth = width/subdivision*widthSub;
            perlinPlane[pointHeight][pointWidth] += 1/(i+1) * plane[pointHeight][pointWidth];  
            

            if(widthSub > 0){  //if this is the first point, no realignment is necessary

                  //Horizontal realignment
             
                    int previousPointWidth = width/subdivision*(widthSub-1);

                    int widthDifference = pointWidth - previousPointWidth;

                    int widthValueDifference = perlinPlane[pointHeight][pointWidth] - perlinPlane[pointHeight][previousPointWidth];
                    for(int w = 0; w < widthDifference; ++w){
                        perlinPlane[heightSub][w] = widthValueDifference/widthDifference*w;
                    }
                

                //Vertical realignment
                  
                        int previousPointHeight = height/subdivision*(heightSub-1); 
                        
                        int heightDifference = pointHeight - previousPointHeight;

                        int heightValueDifference = perlinPlane[pointHeight][pointWidth] - perlinPlane[previousPointHeight][pointWidth];

                        for(int h = 0; h < heightDifference; ++h){
                            perlinPlane[h][widthSub] = widthValueDifference/heightDifference*h;
                        }     
                
            }

             }            
        }
    }   
    
}





struct randomPlane{
    private:
        int height = 0;
        int width = 0;
        int seed;
        
    public:
        double plane[255][255];
        randomPlane(int h, int w, int s) :height{h}, width{w}, seed{s}
        {
            plane[height][width];

            
            for(int i = 0; i < height; ++i){
                
                for(int x = 0; x < width; ++x){
                    
                    int functionSeed = (x == 0)? seed : plane[i][x-1] ;
                    
                    //double randomValue = Mersenne_Twister(9999, 378, 2310, functionSeed);
                    
                    double randomValue = rand();
                    plane[i][x] = randomValue;
                }
                
            }
        }
        

};


int main(){
    

    //create an 
    //For each static row
    cout << "Width: " << endl;

    //Define width and height of the bitmap & select seed for bitmap.
    int width, height, seed;
    cin >> width;
    cout << "Height: " << endl;
    cin >> height;
    cout << "Seed:" << endl;
    cin >> seed;


    randomPlane rando = randomPlane(height, width, seed);

    //int *perlinPlane[height][width];

    //Linear_Perlin(*rando.plane, height, width, 3, *perlinPlane);

    
ofstream img("noise.jpg");
img << "P3" << endl;
img << width << " " << height << endl;
img << "220" << endl;
            
    for(int i = 0; i < height; ++i){
                
        for(int x = 0; x < width; ++x){
            int value = rando.plane[i][x];
            //int value = *perlinPlane[i][x];
                    int r = value % 255;
                    int g = value % 255;
                    int b = value %255;

                    img << r << " " << g << " " << b << endl;
            
        }
                
    }

system("echo 'created image noise.jpg'");
return 0;

}


       