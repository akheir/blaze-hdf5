#include <iostream>
#include <string>
#include <vector>

#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5File.hpp>

#include <blaze/Blaze.h>

const std::string FILE_NAME("create_dataset_example.h5");
const std::string DATASET_NAME("dset");

int main(void) {
    using namespace HighFive;
    try {
        // Create a new file using the default property lists.
        File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);

        blaze::Rand<blaze::DynamicMatrix<double>> gen2{};
        blaze::DynamicMatrix<double> m = gen2.generate(101UL, 101UL);

        std::vector<size_t> dims(2);
        dims[0] = m.rows();
        dims[1] = m.columns();

        for (auto a : dims)
            std::cout << a << ' ';
        std::cout << std::endl;

        // Create the dataset
        DataSet dataset =
                file.createDataSet<double>(DATASET_NAME, DataSpace(dims));

        std::cout << "Number of dimentions:" << dataset.getSpace().getNumberDimensions() << std::endl;

        // write it
        dataset.write(m.data());

    } catch (Exception& err) {
        // catch and print any HDF5 error
        std::cerr << err.what() << std::endl;
    }


//    try {
//        File file(FILE_NAME, File::ReadOnly);
//        DataSet dataset= file.getDataSet(DATASET_NAME);
//        DataSpace dataSpace = dataset.getSpace();
//        std::cout << "Number of dimentions:" << dataSpace.getNumberDimensions() << std::endl;
//        std::vector<std::size_t> dims = dataSpace.getDimensions();
//        for (auto a : dims)
//            std::cout << a << ' ';
//        std::cout << std::endl;
//        std::vector<std::vector<double> > data;
//        dataset.read(data);
//        for (auto a : data) {
//            for (auto b : a)
//                std::cout << b << ' ';
//            std::cout << std::endl;
//        }
//
//    } catch (Exception& err) {
//        // catch and print any HDF5 error
//        std::cerr << err.what() << std::endl;
//    }


    return 0; // successfully terminated
}
