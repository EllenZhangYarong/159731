/**
 * How to use it with the Glass.data:
 * g++ MLP_example.cpp -o MLP_example `pkg-config --cflags --libs opencv`
 *
 * Extract Feature:
 *
 * ./MLP_example -extra dataset_full
 *
 * Train:
 *
 * ./MLP_example -save example.xml -data Glass.data
 *
 *
 * Test:
 *
 * ./MLP_example -load example.xml -data Glass.data
 *
 */

#include <chrono>
#include <ctime>
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <dirent.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include "ASLGuesture.cpp"
#include "BinariseThreshold.cpp"


using namespace std;
using namespace cv;
using namespace chrono;
using namespace cv::ml;


// This function reads data and responses from the file <filename>
static bool
read_num_class_data( const string& filename, int var_count,
                    Mat* _data, Mat* _responses )
{
    const int M = 1024;
    char buf[M+2];
    
    Mat el_ptr(1, var_count, CV_32F);
    int i;
    vector<int> responses;
    
    _data->release();
    _responses->release();
    
    FILE* f = fopen( filename.c_str(), "rt" );
    if( !f )
    {
        cout << "Could not read the database " << filename << endl;
        return false;
    }
    
    for(;;)
    {
        char* ptr;
        if( !fgets( buf, M, f ) || !strchr( buf, ',' ) )
            break;
        cout<< "buf[0] =========> " << buf[0]<<endl;
        responses.push_back(int(buf[0]));
        
        //char test;
        //test=buf[0]+65;
        //responses.push_back(test);
        
        cout << "responses " << buf[0] << " " ;
        
        ptr = buf+3;
        for( i = 0; i < var_count; i++ )
        {
            int n = 0;
            sscanf( ptr, "%f%n", &el_ptr.at<float>(i), &n );
            ptr += n + 1;
        }
        cout << el_ptr << endl;
        if( i < var_count )
            break;
        _data->push_back(el_ptr);
    }
    fclose(f);
    Mat(responses).copyTo(*_responses);
    
    cout << "The database " << filename << " is loaded.\n";
    
    return true;
}

template<typename T>
static Ptr<T> load_classifier(const string& filename_to_load)
{
    // load classifier from the specified file
    Ptr<T> model = StatModel::load<T>( filename_to_load );
    if( model.empty() )
        cout << "Could not read the classifier " << filename_to_load << endl;
    else
        cout << "The classifier " << filename_to_load << " is loaded.\n";
    
    return model;
}

inline TermCriteria TC(int iters, double eps)
{
    return TermCriteria(TermCriteria::MAX_ITER + (eps > 0 ? TermCriteria::EPS : 0), iters, eps);
}

static void test_and_save_classifier(const Ptr<StatModel>& model,
                                     const Mat& data, const Mat& responses,
                                     int ntrain_samples, int rdelta,
                                     const string& filename_to_save)
{
    int i, nsamples_all = data.rows;
    double train_hr = 0, test_hr = 0;
    int training_correct_predict=0;
    // compute prediction error on training data
    for( i = 0; i < nsamples_all; i++ )
    {
        Mat sample = data.row(i);
        cout << "Sample: " << responses.at<int>(i)-48 << " row " << data.row(i) << endl;
        cout << "responses.at<int>(i) --->  " << responses.at<int>(i) << endl;
        cout << "responses.at<int>(i) --->  " << char(responses.at<int>(i)) << endl;
        
        float r = model->predict( sample);
        
        cout << "Predict:  r = " << r << endl;
        if( (int)r == (int)(responses.at<int>(i)-48) || (int)r == (int)(responses.at<int>(i)) )//prediction is correct
            training_correct_predict++;
        
        // r = std::abs(r + rdelta - responses.at<int>(i)) <= FLT_EPSILON ? 1.f : 0.f;
        
        
        //if( i < ntrain_samples )
        //    train_hr += r;
        //else
        //    test_hr += r;
    }
    
    //test_hr /= nsamples_all - ntrain_samples;
    //train_hr = ntrain_samples > 0 ? train_hr/ntrain_samples : 1.;
    printf("ntrain_samples %d training_correct_predict %d \n",ntrain_samples, training_correct_predict);
    if( filename_to_save.empty() )  printf( "\nTest Recognition rate: training set = %.1f%% \n\n", training_correct_predict*100.0/ntrain_samples);
    
    
    if( !filename_to_save.empty() )
    {
        model->save( filename_to_save );
    }
    /*************   Example of how to predict a single sample ************************/
   
    else{
        VideoCapture cap;
        cap.open(0);
        Mat frame;//, image;
        if (!cap.isOpened())
        {
            cout << "Failed to open camera" << endl;
            
        }
        cout << "Opened camera" << endl;
        namedWindow("WebCam", 1);
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        //   cap.set(CV_CAP_PROP_FRAME_WIDTH, 960);
        //   cap.set(CV_CAP_PROP_FRAME_WIDTH, 1600);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        //   cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
        //   cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1200);
        cap >> frame;
        printf("frame size %d %d \n",frame.rows, frame.cols);
        int key=0;
    
    string filename_to_load ;
    string data_filename ;
    
    int method = 0;
    
    double fps=0.0;
    while (1){
        system_clock::time_point start = system_clock::now();
        //for(int a=0;a<10;a++){
        cap >> frame;
        if( frame.empty() )
            break;
        
        char printit[100];
        sprintf(printit,"%2.1f",fps);

        Mat frame_grey;
        cvtColor(frame, frame_grey, CV_BGR2GRAY);
        
        //Code here
        GaussianBlur(frame_grey, frame_grey, Size(5,5), 0);
        BinariseThreshold bt(frame_grey);
        Mat btimage = bt.doBinariseImage();
        ASLGuesture aSLGuesture;
        
        vector<Mat> vmatContourLines1;
        vector<Point> largestContour = aSLGuesture.getContourLine(btimage, vmatContourLines1, 10, 1);
        
        vector<float> CE = aSLGuesture.EllipticFourierDescriptors(largestContour);
        
        int lenCE = CE.size();
        string ceString;
        for(int i = 1; i<lenCE-2;i++){
            
            ceString += to_string(CE[i]) + "," ;
            
        }
        ceString += to_string(CE[19]);
        cout<<"lenCE ---> "<<lenCE<<endl;
        cout<<"ceString ---> "<<ceString<<endl;
        
        CE.erase(CE.begin());
        Mat sample1 ( 1, CE.size(), CV_32F, CE.data());
        float r = model->predict( sample1 );
        cout << "Prediction: " << r << endl;
        char result;
        string strResult;
        if(r>=10){
            result = char(r + 87);
        }else{
            result = char(r + 48);
        }
        cout << "Prediction: " << result << endl;
        stringstream ss;
        
        ss << result;
        ss >> strResult;
        cout << "Prediction: strResult--->" << strResult << endl;

        
        putText(frame, strResult , cvPoint(40,40),FONT_HERSHEY_COMPLEX_SMALL, 2.0, cvScalar(255,0,0), 2, CV_AA);

        imshow("WebCam", frame);
        key=waitKey(1);
        if(key==113 || key==27){
            break;
        } //either esc or 'q'
        
        system_clock::time_point end = system_clock::now();
        
        double seconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
        fps = 1000000*10.0/seconds;
//        fps = 1000000/seconds;
        cout << "frames " << fps << " seconds " << seconds << endl;
    }
    
     /**********************************************************************/
    }
   
    
}

static bool
build_mlp_classifier( const string& data_filename,
                     const string& filename_to_save,
                     const string& filename_to_load)
{
    const int class_count = 36;//CLASSES
    Mat data;
    Mat responses;
    
    bool ok = read_num_class_data( data_filename, 19, &data, &responses );//third parameter: FEATURES
    if( !ok )
        return ok;
    
    Ptr<ANN_MLP> model;
    
    int nsamples_all = data.rows;
    int ntrain_samples = (int)(nsamples_all*1.0);//SPLIT
    
    // Create or load MLP classifier
    if( !filename_to_load.empty() )
    {
        model = load_classifier<ANN_MLP>(filename_to_load);
        if( model.empty() )
            return false;
        //ntrain_samples = 0;
        
    }
    else
    {
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //
        // MLP does not support categorical variables by explicitly.
        // So, instead of the output class label, we will use
        // a binary vector of <class_count> components for training and,
        // therefore, MLP will give us a vector of "probabilities" at the
        // prediction stage
        //
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        Mat train_data = data.rowRange(0, ntrain_samples);
        Mat train_responses = Mat::zeros( ntrain_samples, class_count, CV_32F );
        
        // 1. unroll the responses
        cout << "Unrolling the responses...\n";
        for( int i = 0; i < ntrain_samples; i++ )
        {
            
            int cls_label;
            cls_label= responses.at<int>(i) - 48;// - 'A'; //change to numerical classes, still they read as chars
            
            cout << "labels " << cls_label << endl;
            // cout<< "build_mlp_classifier ---> labels     ---> " <<responses.at<int>(i);
            // cout<< "build_mlp_classifier ---> labels -48 ---> " <<responses.at<int>(i)-48;
            
            train_responses.at<float>(i, cls_label) = 1.f;
        }
        
        // 2. train classifier
        int layer_sz[] = { data.cols, 100, 100, class_count };
        cout <<  " sizeof layer_sz " << sizeof(layer_sz) << " sizeof layer_sz[0]) " << sizeof(layer_sz[0]) << endl;
        int nlayers = (int)(sizeof(layer_sz)/sizeof(layer_sz[0]));
        cout << " nlayers  " << nlayers << endl;
        Mat layer_sizes( 1, nlayers, CV_32S, layer_sz );
        
#if 1
        int method = ANN_MLP::BACKPROP;
        double method_param = 0.001;
        int max_iter = 300;
#else
        int method = ANN_MLP::RPROP;
        double method_param = 0.1;
        int max_iter = 1000;
#endif
        
        Ptr<TrainData> tdata = TrainData::create(train_data, ROW_SAMPLE, train_responses);
        
        cout << "Training the classifier (may take a few minutes)...\n";
        model = ANN_MLP::create();
        model->setLayerSizes(layer_sizes);
        model->setActivationFunction(ANN_MLP::SIGMOID_SYM, 0, 0);
        model->setTermCriteria(TC(max_iter,0));
        model->setTrainMethod(method, method_param);
        model->train(tdata);
        cout << endl;
    }
    
    // test_and_save_classifier(model, data, responses, ntrain_samples, 'A', filename_to_save);
    test_and_save_classifier(model, data, responses, ntrain_samples, 0, filename_to_save);
    return true;
}

void extractFeature(string directory){

    cout<<"ExtractFeature : directory ---> "<<directory<<endl;

    ofstream dataFile;
    string fileName = "Glass.data";
    
    dataFile.open(fileName, ios::in|ios::out|ios::binary | ios::trunc);
    
    if( !dataFile )
    {
        cout << "Could not read the database " << fileName << endl;
    }
    
    else{
        dataFile.clear();
        ASLGuesture aSLGuesture;
        vector<string> files = aSLGuesture.getFilesInDirectory(directory);
        random_shuffle(files.begin(), files.end());
        
        for (auto file : files){
            
            char className = aSLGuesture.getClassIntLabel(file);
            cout << "MAIN: className ----->  "<< className << endl;
            cout << "MAIN: int(className) ----->  "<< int(className) << endl;
            
            string ceString = "";
            int classId;
            
            if(int(className) >= 97){
                classId = int(className)- 97 + 10 ;
            }
            else{
                classId = int(className) - 48;
            }
            cout << "MAIN: classId ----->  "<< classId << endl;
            
            char label = char(classId+48);
            cout << "MAIN: label ----->  "<< label << endl;
            
            ceString += label;
          
            cout<< "Main::ceString ===> "<<ceString<< endl;
            
            Mat image = aSLGuesture.readImage(file);
            
            vector<Mat> vmatContourLines1;
            vector<Point> largestContour = aSLGuesture.getContourLine(image, vmatContourLines1, 10, 1);
            
            vector<float> CE = aSLGuesture.EllipticFourierDescriptors(largestContour);
            
            cout<<"The first of ceString----->"<<ceString<<endl;
            
            for(int i = 1; i<CE.size();i++){
                
                ceString =  ceString + "," + to_string(CE[i]) ;
            }
            ceString += "\n";
            
            cout<<"CE -- > "<< ceString <<endl;
            dataFile << ceString;
        }
        dataFile.close();
        cout<<"Feature extracted completely! \n"<<endl;
    }
}

int main( int argc, char *argv[] )
{
    string filename_to_save = "";
    string filename_to_load = "";
    string data_filename = "";
    string num_classes="";

    
    int i;
    for( i = 1; i < argc; i++ )
    {
        if( strcmp(argv[i],"-extra") == 0){ // flag -extra 
            i++;
            string directory = argv[i];
            extractFeature(directory);
            return 0;
        }
        if( strcmp(argv[i],"-data") == 0 ) // flag "-data letter_recognition.xml"
        {
            i++;
            data_filename = argv[i];
        }
        else if( strcmp(argv[i],"-save") == 0 ) // flag "-save filename.xml"
        {
            i++;
            filename_to_save = argv[i];
            cout << "filename to save is "<< filename_to_save << endl;
        }
        else if( strcmp(argv[i],"-load") == 0) // flag "-load filename.xml"
        {
            i++;
            filename_to_load = argv[i];
        }
        // else if( strcmp(argv[i],"-num") == 0) // flag "-num 36/10"
        // {
        //     i++;
        //     num_classes = argv[i];
        // }

    }
    build_mlp_classifier( data_filename, filename_to_save, filename_to_load);
}
