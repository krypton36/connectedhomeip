# Simulated Device How-To (Linux)

This document contains instructions on how to build, run, and interact with a
simulated device. All virtual accessories live in
[examples/testing-app/linux/apps](../../examples/testing-app/linux/apps).

Each accessory needs to be hosted into a subfolder. It will be the name of the
application. For example `all-clusters-test-app` will create a binary named `chip-all-clusters-test-app`.

If some parameters need to be overridden, a `CHIPProjectConfig.h` file can be
placed under an ‘include’ folder into the app folder. For example
`examples/testing-app/linux/apps/all-clusters-test-app/include/CHIPProjectConfig.h`

In order to generate specific tests for a given accessory, a
[examples/testing-app/linux/apps/all-clusters-test-app/tests.js](../../examples/testing-app/linux/apps/all-clusters-test-app/tests.js)
file can be added into the application directory. The tests listed there are the
one that will be executed once the application has been commissioned.

Simulated Device: simulation of an application in which tests can be added. It
is defined by a ZAP config file and tests can be added with a
[YAML file](../../src/app/tests/suites/certification/Test_TC_DM_1_3_Simulated.yaml).

### Prerequisite

-   [Building Prerequisites](./BUILDING.md#prerequisites)
-   [Prepare For Building](./BUILDING.md#prepare-for-building)

## Generating and building the default Simulated App with Script

In order to utilize the app against a commissioner or controller, the app will
need to be specifically built.

1. To generate the ZAP files, and build the `chip-all-clusters-test-app` binary completing the
   following steps:

    ```
     ./scripts/examples/gn_build_test_example.sh all-clusters-test-app
    ```

## Build the App only

In order to utilize the app against a commissioner or controller, the app will
need to be specifically built.

1. To only build the `chip-all-clusters-test-app` binary completing the following steps:

    ```
    source scripts/activate.sh
    CHIP_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
    GN_ARGS="chip_tests_zap_config=\"all-clusters-test-app\""
    GN_ARGS+="chip_project_config_include_dirs=[\"$CHIP_ROOT/examples/testing-app/linux/apps/all-clusters-test-app/include\", \"$CHIP_ROOT/config/standalone\"]"
    GN_ARGS+="chip_config_network_layer_ble=false"

    gn gen --check --fail-on-unused-args --root=examples/testing-app/linux out/simulated --args="$GN_ARGS"

    ninja -C out/simulated
    ```

## Running the app

Now that the building is completed there is a `chip-all-clusters-test-app` binary created. This
binary can be executed on a linux os.

1. To generate the ZAP files, and build the `chip-all-clusters-test-app` binary completing the
   following steps:

    ```
    ./out/simulated/chip-all-clusters-test-app
    ```

## Running the app with test parameter

Now that the building is completed there is a `chip-all-clusters-test-app` binary created. This
binary can be executed on a linux os with test commands.

1. To generate the ZAP files, and build the `chip-all-clusters-test-app` binary completing the
   following steps:

    ```
    ./out/simulated/chip-all-clusters-test-app --command [TEST NAME]
    ```

## Interacting with the simulated app

Now that the building the app and starting it is complete, you will be able to
interact with it using chip-tool

1. Follow the instruction to build chip-tool in the
   [chip-tool readme](../../examples/chip-tool).

2. Run this command to initiate the pairing.
    ```
    ./out/debug/standalone/chip-tool pairing ethernet 0x654321 20202021 3842 [IP ADDRESS of App] 5542
    ```
3. Run this command to complete the commissioning.
    ```
    ./out/debug/standalone/chip-tool generalcommissioning commissioning-complete 0x654321 0
    ```
4. Most tests will start at this point and now an send cluster commands with
   chip-tool as follow.

    ```
    ./out/debug/standalone/chip-tool onoff on 0x654321 1
    ./out/debug/standalone/chip-tool onoff read on-off 0x654321 1
    ./out/debug/standalone/chip-tool onoff write on-time 1 0x654321 1
    ```

    See [chip-tool readme](../../examples/chip-tool) for additional commands.

## Adding simulated Tests via YAML

In order to validate commissioner/controller behavior, tests need to be added to
the simulated device test framework. To achieve this, YAML files are created and
new code is generated.

1. YAML test file are located in
   [YAML folder](../../src/app/tests/suites/certification/)
2. Test names must follow a strict format dues to CI of test recognition. The
   format is as follows:
    - Test_TC\_[`CATEGORY ABBREVIATION`]\_[`SECTION NUMBER`]\_[`SUBSECTION
      NUMBER`]\_Simulated.yaml
    - <strong>`IMPORTANT`: The test name must end in Simulated with the
      capital.</strong>
3. Available properties can be found in
   [YAML Test Name](../../src/app/tests/suites/README.md)
4. An Additional property is as follows:

    | Name | Description                                                                 |
    | ---- | --------------------------------------------------------------------------- |
    | wait | The command that is expected to be received on the app from the controller. |

5. [Test_TC_DM_1_3_Simulated](../../src/app/tests/suites/certification/Test_TC_DM_1_3_Simulated.yaml)
   is an example of a written test that runs on the simulated device.
6. Next, it will need to be added to
   [examples/testing-app/linux/apps/all-clusters-test-app/tests.js](../../examples/testing-app/linux/apps/all-clusters-test-app/tests.js).
   in the following array
    ```javascript
    const tests = ["Test_TC_DM_1_3_Simulated"];
    ```
7. Then, the code will be generated using ZAP. Follow
   [Gen Script](#generating-and-building-the-default-simulated-app-with-script)
   to do so.
8. When submitting code for review, create 2 commits. One for YAML changes and
   second for generated code.
