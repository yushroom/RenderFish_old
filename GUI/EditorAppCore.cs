using System;
using System.Runtime.InteropServices;
using System.Windows.Media;

namespace GUI
{
    public sealed class EditorAppCoreImporter
    {
#if DEBUG
        const string CORE_DLL_NAME = "GUIEditorCore_d.dll";
#else
        const string CORE_DLL_NAME = "GUIEditorCore.dll";
#endif
        [DllImport(CORE_DLL_NAME)]
        public static extern IntPtr Create(IntPtr native_wnd);
        [DllImport(CORE_DLL_NAME)]
        public static extern void Destroy(IntPtr core);
        [DllImport(CORE_DLL_NAME)]
        public static extern void Refresh(IntPtr core);
        [DllImport(CORE_DLL_NAME)]
        public static extern void Resize(IntPtr core, uint width, uint heith);
    }

    public sealed class EditorAppCore
    {
        private IntPtr _core;

        public EditorAppCore(IntPtr native_wnd)
        {
            _core = EditorAppCoreImporter.Create(native_wnd);
        }
        ~EditorAppCore()
        {
            if (_core != IntPtr.Zero)
            {
                this.Destroy(); 
            }
        }

        public void Destroy()
        {
            EditorAppCoreImporter.Destroy(_core);
            _core = IntPtr.Zero;
        }

        public void Refresh()
        {
            EditorAppCoreImporter.Refresh(_core);
        }

        public void Resize(uint width, uint height)
        {
            EditorAppCoreImporter.Resize(_core, width, height);
        }
    }
}
