add_library(${PROJECT_NAME}_src
        main.cpp Host.cpp Subnet.cpp Range.cpp DataSource.cpp ConfigurationManagerBase.cpp Compressor.cpp OutputManager.cpp
        RawRecordsRecognizer.cpp RecordsProducer.cpp DataProvider.cpp ConfigurationProvider.cpp ConfigurationManager.cpp
        )


add_subdirectory(converting)