###############################################################################
###################### PIC32MZW1 Drvier Configurations ########################
###############################################################################

def importIncFile(component, configName, incFileEntry):
    incFilePath  = incFileEntry[0]
    isEnabled    = incFileEntry[1][0]
    callback     = incFileEntry[1][1]
    dependencies = incFileEntry[1][2]

    incFilePathTup = incFilePath.split('/')

    if len(incFilePathTup) == 1:
        secName = ''
        incFile = incFilePathTup[0]
    else:
        secName = incFilePathTup[0]
        incFile = incFilePathTup[1]

    symName = incFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    incFileSym = component.createFileSymbol(symName, None)
    incFileSym.setSourcePath('driver/pic32mzw1/' + secSName + 'include/' + incFile)
    incFileSym.setOutputName(incFile)
    incFileSym.setDestPath('driver/wifi/pic32mzw1/include/' + secDName)
    incFileSym.setProjectPath('config/' + configName + '/driver/wifi/pic32mzw1/include/' + secDName)
    incFileSym.setType('HEADER')
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)

def importSrcFile(component, configName, srcFileEntry):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit('/', 1)

    if len(srcFilePathTup) == 1:
        secName = ''
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ''
    symName = srcFile.replace('.', '_').upper()
    secSName = secName + '/'
    secDName = secSName

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath('driver/pic32mzw1/' + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit('/', 1)[-1])
    srcFileSym.setDestPath('driver/wifi/pic32mzw1/' + secDName)
    srcFileSym.setProjectPath('config/' + configName + '/driver/wifi/pic32mzw1/' + secDName)
    srcFileSym.setType('SOURCE')
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)

def setIncPath(component, configName, incPathEntry):
    incPath      = incPathEntry[0]
    isEnabled    = incPathEntry[1][0]
    callback     = incPathEntry[1][1]
    dependencies = incPathEntry[1][2]

    incPathSym = component.createSettingSymbol('PIC32MZW1_INC_PATH' + incPath.replace('.', '_').replace('/', '_').upper(), None)
    incPathSym.setValue('../src/config/' + configName + '/driver/wifi/pic32mzw1/include' + incPath + ';')
    incPathSym.setCategory('C32')
    incPathSym.setKey('extra-include-directories')
    incPathSym.setAppend(True, ';')
    incPathSym.setEnabled(isEnabled)
    incPathSym.setDependencies(callback, dependencies)

def instantiateComponent(drvPic32mzw1Component):
    print('PIC32MZW1 Driver Component')
    configName = Variables.get('__CONFIGURATION_NAME')

    drvPic32mzw1Component.setCapabilityEnabled("libdrvPic32mzw1Mac", True)

    # Log Level
    pic32mzw1LogLevel = drvPic32mzw1Component.createComboSymbol('DRV_WIFI_PIC32MZW1_LOG_LEVEL', None, ['None', 'Error', 'Inform', 'Trace', 'Verbose'])
    pic32mzw1LogLevel.setLabel('Driver Log Level')
    pic32mzw1LogLevel.setVisible(True)
    pic32mzw1LogLevel.setDefaultValue('Trace')

    # RTOS Configuration
    pic32mzw1RtosMenu = drvPic32mzw1Component.createMenuSymbol('DRV_WIFI_PIC32MZW1_RTOS_MENU', None)
    pic32mzw1RtosMenu.setLabel('RTOS Configuration')
    pic32mzw1RtosMenu.setDescription('RTOS Configuration')
    pic32mzw1RtosMenu.setVisible(False)
    pic32mzw1RtosMenu.setVisible((Database.getSymbolValue('HarmonyCore', 'SELECT_RTOS') != 'BareMetal') and (Database.getSymbolValue('HarmonyCore', 'SELECT_RTOS') != None))
    pic32mzw1RtosMenu.setDependencies(setVisibilityRTOSMenu, ['HarmonyCore.SELECT_RTOS'])

    # RTOS Execution Mode
    pic32mzw1InstnExecMode = drvPic32mzw1Component.createComboSymbol('DRV_WIFI_PIC32MZW1_RTOS', pic32mzw1RtosMenu, ['Standalone'])
    pic32mzw1InstnExecMode.setLabel('Run Driver Tasks as')
    pic32mzw1InstnExecMode.setVisible(False)
    pic32mzw1InstnExecMode.setDescription('WiFi PIC32MZW1 Driver RTOS Execution Mode')
    pic32mzw1InstnExecMode.setDefaultValue('Standalone')

    # WiFi Driver Task Stack Size
    pic32mzw1TaskSize = drvPic32mzw1Component.createIntegerSymbol('DRV_WIFI_PIC32MZW1_RTOS_STACK_SIZE', pic32mzw1RtosMenu)
    pic32mzw1TaskSize.setLabel('Task Size')
    pic32mzw1TaskSize.setVisible(True)
    pic32mzw1TaskSize.setDescription('WiFi PIC32MZW1 Driver RTOS Task Stack Size')
    pic32mzw1TaskSize.setDefaultValue(1024)
    pic32mzw1TaskSize.setDependencies(setVisibilityRTOSTaskConfig, ['DRV_WIFI_PIC32MZW1_RTOS'])

    # WiFi Driver Task Priority
    pic32mzw1TaskPriority = drvPic32mzw1Component.createIntegerSymbol('DRV_WIFI_PIC32MZW1_RTOS_TASK_PRIORITY', pic32mzw1RtosMenu)
    pic32mzw1TaskPriority.setLabel('Task Priority')
    pic32mzw1TaskPriority.setVisible(True)
    pic32mzw1TaskPriority.setDescription('WiFi PIC32MZW1 Driver RTOS Task Priority')
    pic32mzw1TaskPriority.setDefaultValue(1)
    pic32mzw1TaskPriority.setDependencies(setVisibilityRTOSTaskConfig, ['DRV_WIFI_PIC32MZW1_RTOS'])

    # WiFi Use Task Delay?
    pic32mzw1UseTaskDelay = drvPic32mzw1Component.createBooleanSymbol('DRV_WIFI_PIC32MZW1_RTOS_USE_DELAY', pic32mzw1RtosMenu)
    pic32mzw1UseTaskDelay.setLabel('Use Task Delay?')
    pic32mzw1UseTaskDelay.setVisible(True)
    pic32mzw1UseTaskDelay.setDescription('WiFi PIC32MZW1 Driver Task Uses Delay?')
    pic32mzw1UseTaskDelay.setDefaultValue(True)
    pic32mzw1UseTaskDelay.setDependencies(setVisibilityRTOSTaskConfig, ['DRV_WIFI_PIC32MZW1_RTOS'])

    # WiFi Driver Task Delay
    pic32mzw1DrvTaskDelay = drvPic32mzw1Component.createIntegerSymbol('DRV_WIFI_PIC32MZW1_RTOS_DELAY', pic32mzw1RtosMenu)
    pic32mzw1DrvTaskDelay.setLabel('Task Delay')
    pic32mzw1DrvTaskDelay.setVisible(True)
    pic32mzw1DrvTaskDelay.setDescription('WiFi Driver Task Delay')
    pic32mzw1DrvTaskDelay.setDefaultValue(1)
    pic32mzw1DrvTaskDelay.setDependencies(setVisibilityRTOSTaskDelay, ['DRV_WIFI_PIC32MZW1_RTOS', 'DRV_WIFI_PIC32MZW1_RTOS_USE_DELAY'])

    ############################################################################
    #### Code Generation ####
    ############################################################################

    condAlways = [True, None, []]

    wdrvIncFiles = [
        ['drv_pic32mzw1.h',             condAlways],
        ['wdrv_pic32mzw.h',             condAlways],
        ['wdrv_pic32mzw_api.h',         condAlways],
        ['wdrv_pic32mzw_assoc.h',       condAlways],
        ['wdrv_pic32mzw_authctx.h',     condAlways],
        ['wdrv_pic32mzw_bssctx.h',      condAlways],
        ['wdrv_pic32mzw_bssfind.h',     condAlways],
        ['wdrv_pic32mzw_cfg.h',         condAlways],
        ['wdrv_pic32mzw_client_api.h',  condAlways],
        ['wdrv_pic32mzw_common.h',      condAlways],
        ['wdrv_pic32mzw_debug.h',       condAlways],
        ['wdrv_pic32mzw_mac.h',         condAlways],
        ['wdrv_pic32mzw_softap.h',      condAlways],
        ['wdrv_pic32mzw_sta.h',         condAlways]
    ]

    for incFileEntry in wdrvIncFiles:
        importIncFile(drvPic32mzw1Component, configName, incFileEntry)

    wdrvSrcFiles = [
        ['wdrv_pic32mzw.c',             condAlways],
        ['wdrv_pic32mzw_assoc.c',       condAlways],
        ['wdrv_pic32mzw_authctx.c',     condAlways],
        ['wdrv_pic32mzw_bssctx.c',      condAlways],
        ['wdrv_pic32mzw_bssfind.c',     condAlways],
        ['wdrv_pic32mzw_cfg.c',         condAlways],
        ['wdrv_pic32mzw_int.c',         condAlways],
        ['wdrv_pic32mzw_softap.c',      condAlways],
        ['wdrv_pic32mzw_sta.c',         condAlways]
    ]

    for srcFileEntry in wdrvSrcFiles:
        importSrcFile(drvPic32mzw1Component, configName, srcFileEntry)

    wdrvIncPaths = [
        ['/', condAlways]
    ]

    for incPathEntry in wdrvIncPaths:
        setIncPath(drvPic32mzw1Component, configName, incPathEntry)

    pic32mzw1_a = drvPic32mzw1Component.createLibrarySymbol(None, None)
    pic32mzw1_a.setDestPath('driver/wifi/pic32mzw1/lib')
    pic32mzw1_a.setOutputName('pic32mzw1.a')
    pic32mzw1_a.setSourcePath('driver\pic32mzw1/pic32mzw1.a')

    drvpic32mzw1SystemDefFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_DEF', None)
    drvpic32mzw1SystemDefFile.setType('STRING')
    drvpic32mzw1SystemDefFile.setOutputName('core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES')
    drvpic32mzw1SystemDefFile.setSourcePath('driver/pic32mzw1/templates/system/system_definitions.h.ftl')
    drvpic32mzw1SystemDefFile.setMarkup(True)

    drvpic32mzw1SystemDefObjFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_SYSTEM_DEF_OBJECT', None)
    drvpic32mzw1SystemDefObjFile.setType('STRING')
    drvpic32mzw1SystemDefObjFile.setOutputName('core.LIST_SYSTEM_DEFINITIONS_H_OBJECTS')
    drvpic32mzw1SystemDefObjFile.setSourcePath('driver/pic32mzw1/templates/system/system_definitions_objects.h.ftl')
    drvpic32mzw1SystemDefObjFile.setMarkup(True)

    drvpic32mzw1SystemConfFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_SYSTEM_CFG', None)
    drvpic32mzw1SystemConfFile.setType('STRING')
    drvpic32mzw1SystemConfFile.setOutputName('core.LIST_SYSTEM_CONFIG_H_DRIVER_CONFIGURATION')
    drvpic32mzw1SystemConfFile.setSourcePath('driver/pic32mzw1/templates/system/system_config.h.ftl')
    drvpic32mzw1SystemConfFile.setMarkup(True)

    drvpic32mzw1SystemInitDataFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_INIT_DATA', None)
    drvpic32mzw1SystemInitDataFile.setType('STRING')
    drvpic32mzw1SystemInitDataFile.setOutputName('core.LIST_SYSTEM_INIT_C_DRIVER_INITIALIZATION_DATA')
    drvpic32mzw1SystemInitDataFile.setSourcePath('driver/pic32mzw1/templates/system/system_initialize_data.c.ftl')
    drvpic32mzw1SystemInitDataFile.setMarkup(True)

    drvpic32mzw1SystemInitFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_SYS_INIT', None)
    drvpic32mzw1SystemInitFile.setType('STRING')
    drvpic32mzw1SystemInitFile.setOutputName('core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS')
    drvpic32mzw1SystemInitFile.setSourcePath('driver/pic32mzw1/templates/system/system_initialize.c.ftl')
    drvpic32mzw1SystemInitFile.setMarkup(True)

    drvpic32mzw1SystemTaskFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_SYSTEM_TASKS_C', None)
    drvpic32mzw1SystemTaskFile.setType('STRING')
    drvpic32mzw1SystemTaskFile.setOutputName('core.LIST_SYSTEM_TASKS_C_CALL_DRIVER_TASKS')
    drvpic32mzw1SystemTaskFile.setSourcePath('driver/pic32mzw1/templates/system/system_tasks.c.ftl')
    drvpic32mzw1SystemTaskFile.setMarkup(True)

    drvpic32mzw1SystemRtosTasksFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_SYS_RTOS_TASK', None)
    drvpic32mzw1SystemRtosTasksFile.setType('STRING')
    drvpic32mzw1SystemRtosTasksFile.setOutputName('core.LIST_SYSTEM_RTOS_TASKS_C_DEFINITIONS')
    drvpic32mzw1SystemRtosTasksFile.setSourcePath('driver/pic32mzw1/templates/system/system_rtos_tasks.c.ftl')
    drvpic32mzw1SystemRtosTasksFile.setMarkup(True)
    drvpic32mzw1SystemRtosTasksFile.setEnabled((Database.getSymbolValue('HarmonyCore', 'SELECT_RTOS') != 'BareMetal'))
    drvpic32mzw1SystemRtosTasksFile.setDependencies(setEnabledRTOSTask, ['HarmonyCore.SELECT_RTOS'])

    drvpic32mzw1IntWeakHandleFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_INTERRUPT_WEAK_HANDLERS', None)
    drvpic32mzw1IntWeakHandleFile.setType('STRING')
    drvpic32mzw1IntWeakHandleFile.setOutputName('core.LIST_SYSTEM_INTERRUPT_WEAK_HANDLERS')
    drvpic32mzw1IntWeakHandleFile.setSourcePath('driver/pic32mzw1/templates/system/interrupts_weak_handlers.h.ftl')
    drvpic32mzw1IntWeakHandleFile.setMarkup(True)

    drvpic32mzw1IntTableFile = drvPic32mzw1Component.createFileSymbol('DRV_WIFI_PIC32MZW1_INTERRUPT_HANDLERS', None)
    drvpic32mzw1IntTableFile.setType('STRING')
    drvpic32mzw1IntTableFile.setOutputName('core.LIST_SYSTEM_INTERRUPT_HANDLERS')
    drvpic32mzw1IntTableFile.setSourcePath('driver/pic32mzw1/templates/system/interrupts_vector_table.h.ftl')
    drvpic32mzw1IntTableFile.setMarkup(True)

def setVisibilityRTOSMenu(symbol, event):
    if (event['value'] == None):
        symbol.setVisible(False)
    elif (event['value'] != 'BareMetal'):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

def setVisibilityRTOSTaskConfig(symbol, event):
    if (event['value'] == 'Standalone'):
        symbol.setVisible(True)
        print('WiFi Standalone')
    else:
        symbol.setVisible(False)
        print('WiFi Combined')

def setVisibilityRTOSTaskDelay(symbol, event):
    drvWifiRtos = symbol.getComponent().getSymbolByID(event['id'])
    if(drvWifiRtos.getValue() == True):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

def setEnabledRTOSTask(symbol, event):
    symbol.setEnabled((Database.getSymbolValue('HarmonyCore', 'SELECT_RTOS') != 'BareMetal'))
