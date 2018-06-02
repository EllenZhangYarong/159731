/**
 * How to use it with the Glass.data:
 * g++ MLP_example.cpp -o MLP_example `pkg-config --cflags --libs opencv`
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

#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"

#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;
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

cout << "responses " << buf[0] << " " ;;//<<  endl;
// cout << "responses " << buf[1] << " " ;;//<<  endl;
// cout << "responses " << buf[2] << " " ;;//<<  endl;

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
// Use that for the assignment3, for every frame after computing the features, r is the prediction given the features listed in this format
    // Mat sample = data.row(i);
//     Mat sample1 = (Mat_<float>(1,19) << 0.75045002, 0.165103, 0.228174, 0.25637999, 0.072705999, 0.089318, 0.105336, 0.034935001, 0.029279999, 0.034175001, 0.029263999, 0.046624001, 0.0081160003, 0.015915999, 0.022166001, 0.012854, 0.013284, 0.0075289998, 0.010485);// 8
//     float r = model->predict( sample1 );
//     cout << "Prediction: " << r << endl;
//     // sample1 = (Mat_<float>(1,19) << 0.223290,0.102930,0.088691,0.080694,0.041730,0.040103,0.029981,0.023284,0.011648,0.015089,0.007306,0.015733,0.015540,0.016246,0.014622,0.013004,0.009342,0.010070,0.006835);//102
//     // r = model->predict( sample1 );
//     // cout << "Prediction: " << r << endl;
//     // sample1 = (Mat_<float>(1,19) << 0.144282,0.087850,0.052493,0.072065,0.011268,0.042668,0.009383,0.017406,0.011594,0.018039,0.018617,0.007523,0.007635,0.018995,0.014210,0.014785,0.008851,0.007116,0.008325);//97
//     r = model->predict( sample1 );
//     cout << "Prediction: " << r << endl;
// //    sample1 = (Mat_<float>(1,9) << );//4
// //    r = model->predict( sample1 );
// //    cout << "Prediction: " << r << endl;
//     sample1 = (Mat_<float>(1,19) << 0.566817,0.313831,0.320895,0.249678,0.056314,0.094310,0.028643,0.071346,0.038398,0.035471,0.008978,0.023762,0.025129,0.014762,0.026138,0.009743,0.019700,0.021664,0.009093);//1
//     r = model->predict( sample1 );
//     cout << "Prediction: " << r << endl;
//     sample1 = (Mat_<float>(1,19) << 0.91470402, 0.18465801, 0.376185, 0.334075, 0.167271, 0.064267002, 0.045953002, 0.053263001, 0.053946, 0.027945001, 0.029453, 0.019339001, 0.031074001, 0.016324, 0.010249, 0.029611999, 0.014523, 0.011539, 0.0069590001);//9

//     r = model->predict( sample1 );
//     cout << "Prediction: " << r << endl;
//     sample1 = (Mat_<float>(1,19) <<0.140279, 0.136648, 0.074612997, 0.033139002, 0.032421999, 0.017703, 0.023073001, 0.012526, 0.0058090002, 0.0097770002, 0.0082710003, 0.0040759998, 0.0031030001, 0.0054580001, 0.0040250001, 0.001297, 0.0049129999, 0.001648, 0.002167);//0

//     r = model->predict( sample1 );
//     cout << "Prediction: " << r << endl;

//113,0.407731,0.379642,0.197536,0.132654,0.036822,0.030274,0.041858,0.044600,0.020604,0.013113,0.012526,0.010469,0.004555,0.013772,0.012837,0.010193,0.003943,0.004218,0.004693
//118,0.707533,0.307887,0.323476,0.147875,0.047717,0.056013,0.022244,0.019373,0.035870,0.026709,0.044966,0.008745,0.011725,0.014581,0.010060,0.008264,0.011793,0.013919,0.013768
//112,0.560176,0.237944,0.241784,0.092851,0.100642,0.067630,0.034058,0.033118,0.024629,0.037711,0.029163,0.034023,0.027838,0.009543,0.008445,0.013333,0.003941,0.010523,0.006394
//120,0.373308,0.165331,0.193107,0.094597,0.086190,0.045220,0.043897,0.014988,0.027343,0.026252,0.014751,0.025330,0.017565,0.008116,0.003362,0.006371,0.011607,0.005848,0.010180
    
/**********************************************************************/    
    
}



static bool
build_mlp_classifier( const string& data_filename,
                      const string& filename_to_save,
                      const string& filename_to_load )
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

int main( int argc, char *argv[] )
{
    string filename_to_save = "";
    string filename_to_load = "";
    string data_filename = "Glass.data";
    int method = 0;

    int i;
    for( i = 1; i < argc; i++ )
    {
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
    }
    build_mlp_classifier( data_filename, filename_to_save, filename_to_load );
}
