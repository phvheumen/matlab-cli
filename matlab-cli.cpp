#include "MatlabEngine.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        // Connect to shared MATLAB engine session
        std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::connectMATLAB();

        if (argc == 1)
        {
            while (matlabPtr != nullptr)
            {
                auto out = std::make_shared<std::basic_stringbuf<char16_t>>();
                auto err = std::make_shared<std::basic_stringbuf<char16_t>>();

                std::cout << ">> ";

                std::string _cmdline;
                std::getline(std::cin, _cmdline);

                auto cmdline = matlab::engine::convertUTF8StringToUTF16String(_cmdline);

                try
                {
                    matlabPtr->eval(cmdline, out, err);
                }
                catch (const matlab::engine::MATLABExecutionException &e)
                {
                    matlab::engine::String err_ = err.get()->str();
                    std::cerr << matlab::engine::convertUTF16StringToUTF8String(err_);
                }
                catch (const matlab::engine::MATLABSyntaxException &e)
                {
                    matlab::engine::String err_ = err.get()->str();
                    std::cerr << matlab::engine::convertUTF16StringToUTF8String(err_);
                }
                catch (const matlab::engine::MATLABNotAvailableException &e)
                {
                    std::cerr << "error: MATLAB session not available" << std::endl;
                    return 1;
                }
                catch (const matlab::engine::Exception &e)
                {
                    std::cerr << "error: Exception occured" << std::endl;
                    throw(e);
                }

                matlab::engine::String out_ = out.get()->str();
                std::cout << matlab::engine::convertUTF16StringToUTF8String(out_);
            }
        }
        else
        {
            auto out = std::make_shared<std::basic_stringbuf<char16_t>>();
            auto err = std::make_shared<std::basic_stringbuf<char16_t>>();

            std::string _mscript(argv[1]);
            std::string _cmdline("run('" + _mscript + "');");
            auto cmdline = matlab::engine::convertUTF8StringToUTF16String(_cmdline);

            try
            {
                matlabPtr->eval(cmdline, out, err);
            }
            catch (const matlab::engine::MATLABExecutionException &e)
            {
                matlab::engine::String err_ = err.get()->str();
                std::cerr << matlab::engine::convertUTF16StringToUTF8String(err_);
            }
            catch (const matlab::engine::MATLABSyntaxException &e)
            {
                matlab::engine::String err_ = err.get()->str();
                std::cerr << matlab::engine::convertUTF16StringToUTF8String(err_);
            }
            catch (const matlab::engine::MATLABNotAvailableException &e)
            {
                std::cerr << "error: MATLAB session not available" << std::endl;
                return 1;
            }
            catch (const matlab::engine::Exception &e)
            {
                std::cerr << "error: Exception occured" << std::endl;
                throw(e);
            }

            matlab::engine::String out_ = out.get()->str();
            std::cout << matlab::engine::convertUTF16StringToUTF8String(out_);
        }
    }
    catch (const matlab::engine::EngineException &e)
    {
        std::cerr << "error: Could not connect to a MATLAB session" << std::endl;
        return 1;
    }

    return 0;
}