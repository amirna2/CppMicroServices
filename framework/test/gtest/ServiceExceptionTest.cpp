/*=============================================================================

Library: CppMicroServices

Copyright (c) The CppMicroServices developers. See the COPYRIGHT
file at the top-level directory of this distribution and at
https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=============================================================================*/

#include "cppmicroservices/FrameworkFactory.h"
#include "cppmicroservices/Framework.h"
#include "cppmicroservices/BundleContext.h"
#include "gtest/gtest.h"

using namespace cppmicroservices;

TEST(ServiceExceptionTest, TestServiceException)
{
  FrameworkFactory factory;
  auto framework = factory.NewFramework();
  framework.Start();
  auto context = framework.GetBundleContext();

  // Test ServiceException assignment and ostream operations.
  // We artifically throw the exception by getting a "void" ServiceReference.
  ASSERT_THROW(context.GetServiceReferences<void>(), ServiceException);
  try
  {
    auto refs = context.GetServiceReferences<void>();
  }
  catch (const ServiceException& se)
  {
    ServiceException other_se = se;
    other_se = se;
    std::string expected_prefix = "ServiceException: ";
    std::ostringstream strstream;
    strstream << other_se;
    ASSERT_TRUE(strstream.str().compare(0, expected_prefix.length(), expected_prefix) == 0);
  }
}